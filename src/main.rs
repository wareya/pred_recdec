mod bnf;
use bnf::*;

mod pred_recdec;
#[allow(unused)]
use pred_recdec::*;


// Removed the main function as it was extraneous.
fn main() {
    let grammar_source = std::fs::read_to_string("src/grammar.txt").unwrap();
    
    let mut g = bnf_to_grammar(&grammar_source).unwrap();
    
    //let test_source = std::fs::read_to_string("src/test_pp_gcc.c").unwrap();
    let test_source = std::fs::read_to_string("src/test_pp_clang.c").unwrap();
    
    let tokens = tokenize(&mut g, &test_source);
    let tokens = tokens.unwrap();
    //let tokens = tokenize(&mut g, &"9152 6 3");

    println!("{:#?}", &tokens[..tokens.len().min(10)]);
    
    let start = std::time::Instant::now();
    
    use std::rc::Rc;
    use rustc_hash::FxBuildHasher;
    type HashMap<K, V> = std::collections::HashMap::<K, V, FxBuildHasher>;
    type HashSet<V> = std::collections::HashSet::<V, FxBuildHasher>;

    let mut hooks : HashMap<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], usize, &mut Vec<Box<ASTNode>>) -> Result<usize, String>>>
        = <_>::default();
    let mut guards = HashMap::<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], _) -> GuardResult>>::default();
    
    type typedef_stacks = Vec<HashSet<Rc<String>>>;
    type enum_stacks = Vec<HashSet<Rc<String>>>;
    
    let type_specifier_checker : Rc<dyn Fn(&mut PrdGlobal, &[Token], usize) -> GuardResult>
        = Rc::new(|global : &mut PrdGlobal, tokens : &[Token], i : usize|
    {
        if i < tokens.len()
        {
            let n = &tokens[i].text;
            let r = global.udata_r.entry(15238539).or_insert_with(|| RegexCacher::new(regex::Regex::new(
                r#"(?x)\A(?:void|__attribute__|__extension__|__builtin_va_list|char|short|int|long|float|double|signed|unsigned|_Bool|_Complex|_Imaginary|enum|struct|union)\z"#
            ).unwrap()));
            if r.is_match(n)
            {
                println!("!!!! accepting {n} as a type indicator");
                return GuardResult::Accept;
            }
            if let Some(stacks) = global.udata.get::<typedef_stacks>()
            {
                for s in stacks
                {
                    if s.contains(n)
                    {
                        println!("!!!! accepting {n} as a typedef (type specifier)");
                        return GuardResult::Accept;
                    }
                }
            }
        }
        GuardResult::Reject
    });
    
    guards.insert("is_type_specifier_start".to_string(),
        Rc::clone(&type_specifier_checker)
    );
    
    guards.insert("is_declaration_indicator".to_string(),
        Rc::new(|global : &mut PrdGlobal, tokens : &[Token], i : usize|
        {
            if i < tokens.len()
            {
                let n = &tokens[i].text;
                let r = global.udata_r.entry(75425463).or_insert_with(|| RegexCacher::new(regex::Regex::new(
                    r#"(?x)\A(?:typedef|extern|__attribute__|__extension__|__builtin_va_list|static|auto|register|const|restrict|__restrict__|volatile|__volatile__|__inline__|__inline|inline|void|char|short
                    |int|long|float|double|signed|unsigned|_Bool|_Complex|_Imaginary|enum|struct|union)\z"#
                ).unwrap()));
                if r.is_match(n)
                {
                    println!("!!!! accepting {n} as a declaration indicator");
                    return GuardResult::Accept;
                }
                if let Some(stacks) = global.udata.get::<typedef_stacks>()
                {
                    for s in stacks
                    {
                        if s.contains(n)
                        {
                            println!("!!!! accepting {n} as a typedef");
                            return GuardResult::Accept;
                        }
                    }
                }
            }
            GuardResult::Reject
        }
    ));
    
    guards.insert("is_label".to_string(),
        Rc::new(|global : &mut PrdGlobal, tokens : &[Token], i : usize|
        {
            if i + 1 < tokens.len()
            {
                let n = &tokens[i].text;
                let n2 = &tokens[i+1].text;
                let r = global.udata_r.entry(648245613).or_insert_with(|| RegexCacher::new(regex::Regex::new(
                    r#"^(?:[a-zA-Z_]|(?:\\u[a-fA-F0-9]{1,4}|\\U[a-fA-F0-9]{1,8}))(?:[a-zA-Z_]|(?:\\u[a-fA-F0-9]{1,4}|\\U[a-fA-F0-9]{1,8})|[0-9])*$"#
                ).unwrap()));
                if &**n2 == ":" && r.is_match(n)
                {
                    return GuardResult::Accept;
                }
            }
            GuardResult::Reject
        }
    ));
    
    let f = Rc::clone(&type_specifier_checker);
    guards.insert("is_primitive_cast".to_string(),
        Rc::new(move |global : &mut PrdGlobal, tokens : &[Token], i : usize|
        {
            if i < tokens.len()
            {
                let n = &tokens[i].text;
                if &**n == "("
                {
                    if !matches!(f(global, tokens, i+1), GuardResult::Accept)
                    {
                        return GuardResult::Reject;
                    }
                    let i2 = i.strict_add_signed(tokens[i].pair);
                    let i3 = i2 + 1;
                    if i3 < tokens.len()
                    {
                        if &**tokens[i3].text == "{"
                        {
                            return GuardResult::Reject;
                        }
                    }
                    return GuardResult::Accept;
                }
            }
            GuardResult::Reject
        }
    ));
    
    guards.insert("is_ident_not_known_enum".to_string(),
        Rc::new(|global : &mut PrdGlobal, tokens : &[Token], i : usize|
        {
            if i < tokens.len()
            {
                let n = &tokens[i].text;
                let r = global.udata_r.entry(648245613).or_insert_with(|| RegexCacher::new(regex::Regex::new(
                    r#"^(?:[a-zA-Z_]|(?:\\u[a-fA-F0-9]{1,4}|\\U[a-fA-F0-9]{1,8}))(?:[a-zA-Z_]|(?:\\u[a-fA-F0-9]{1,4}|\\U[a-fA-F0-9]{1,8})|[0-9])*$"#
                ).unwrap()));
                if r.is_match(n)
                {
                    let mut stacks = global.udata.get_mut::<typedef_stacks>();
                    let stacks = stacks.as_mut().unwrap();
                    for s in stacks.iter()
                    {
                        if s.contains(n)
                        {
                            return GuardResult::Reject;
                        }
                    }
                    return GuardResult::Accept;
                }
            }
            GuardResult::Reject
        }
    ));
    
    guards.insert("is_known_enum".to_string(),
        Rc::new(|global : &mut PrdGlobal, tokens : &[Token], i : usize|
        {
            if i < tokens.len()
            {
                let n = &tokens[i].text;
                let mut stacks = global.udata.get_mut::<typedef_stacks>();
                let stacks = stacks.as_mut().unwrap();
                for s in stacks.iter()
                {
                    if s.contains(n)
                    {
                        return GuardResult::Accept;
                    }
                }
            }
            GuardResult::Reject
        }
    ));
    
    hooks.insert("init".to_string(),
        Rc::new(|global : &mut PrdGlobal, _tokens : &[Token], _i : usize, _children : &mut Vec<Box<ASTNode>>|
        {
            let mut s = typedef_stacks::new();
            let mut s2 = enum_stacks::new();
            s.push(<_>::default());
            s2.push(<_>::default());
            global.udata.insert(s);
            global.udata.insert(s2);
            Ok(0)
        }
    ));
    
    hooks.insert("typedef_stack_push".to_string(),
        Rc::new(|global : &mut PrdGlobal, tokens : &[Token], i : usize, children : &mut Vec<Box<ASTNode>>|
        {
            let mut stacks = global.udata.get_mut::<typedef_stacks>();
            let stacks = stacks.as_mut().unwrap();
            stacks.push(<_>::default());
            let mut stacks = global.udata.get_mut::<enum_stacks>();
            let stacks = stacks.as_mut().unwrap();
            stacks.push(<_>::default());
            Ok(0)
        }
    ));
    hooks.insert("typedef_stack_pop".to_string(),
        Rc::new(|global : &mut PrdGlobal, tokens : &[Token], i : usize, children : &mut Vec<Box<ASTNode>>|
        {
            let mut stacks = global.udata.get_mut::<typedef_stacks>();
            let stacks = stacks.as_mut().unwrap();
            stacks.pop();
            let mut stacks = global.udata.get_mut::<enum_stacks>();
            let stacks = stacks.as_mut().unwrap();
            stacks.pop();
            Ok(0)
        }
    ));
    hooks.insert("typedefs_log".to_string(),
        Rc::new(|global : &mut PrdGlobal, tokens : &[Token], i : usize, children : &mut Vec<Box<ASTNode>>|
        {
            let mut stacks = global.udata.get_mut::<typedef_stacks>();
            let stacks = stacks.as_mut().unwrap();
            if let Some(s) = stacks.last_mut()
            {
                let mut found = false;
                let mut f : &mut dyn FnMut(&ASTNode) -> bool = &mut |c : &ASTNode|
                {
                    if c.children.is_none() && *c.text == "typedef" { found = true; }
                    if c.children.is_some() && *c.text == "type_specifier" { return false; }
                    true
                };
                for c in children.iter_mut()
                {
                    visit_mut(c, &mut f);
                }
                
                if found
                {
                    let mut f2 : &mut dyn FnMut(&ASTNode) -> bool = &mut |c : &ASTNode|
                    {
                        if c.children.is_some() && *c.text == "identifier" && c.children.is_some()
                        {
                            s.insert(Rc::clone(&c.children.as_ref().unwrap()[0].text));
                        }
                        if c.children.is_some() && *c.text == "type_specifier" { return false; }
                        true
                    };
                    for c in children.iter_mut()
                    {
                        visit_mut(c, &mut f2);
                    }
                }
            }
            //println!("-------");
            Ok(0)
        }
    ));
    
    hooks.insert("many_balanced".to_string(),
        Rc::new(|global : &mut PrdGlobal, tokens : &[Token], mut i : usize, children : &mut Vec<Box<ASTNode>>|
        {
            let mut balance = 0;
            let start = i;
            while i < tokens.len() && balance >= 0
            {
                if tokens[i].pair > 0 { balance += 1; }
                else if tokens[i].pair < 0 { balance -= 1; }
                if balance >= 0
                {
                    children.push(Box::new(ASTNode {
                        text : tokens[i].text.clone(), children : None,
                        token_start : i, token_count : 1, poisoned : false
                    }));
                    i += 1;
                }
            }
            Ok(i-start)
        }
    ));
    
    let ast = pred_recdec_parse(&g, "S", &tokens[..], guards, hooks);
    //println!("{}", ast.is_ok());
    println!("Time taken: {:?} under {} items", start.elapsed(), tokens.len());
    //let ast = ast.unwrap();
    //println!("{:#?} {} {} {} {}", ast, ast.text, ast.children.as_ref().unwrap().len(), ast.token_start, ast.token_count);
    //print_ast_earley(&ast.unwrap(), 0);
    //print_ast_packrat(&ast.unwrap(), 0);
    //print_ast_brute_force(&ast.unwrap(), 0);
    print_ast_pred_recdec(&ast.unwrap(), 0);
}
