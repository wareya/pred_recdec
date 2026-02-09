use mimalloc::MiMalloc;
#[global_allocator]
static GLOBAL: MiMalloc = MiMalloc;

pub use rustc_hash::FxBuildHasher as HashBuilder;

use pred_recdec::bnf::*;
use pred_recdec::ast::*;

fn main()
{
    let args: Vec<String> = std::env::args().collect();

    println!("usage: cargo test test_c --release -- <filename>.c --show-output");
    if args.len() < 3
    {
        return;
    }
    let input_fname = args[2].to_string();
    
    let start = std::time::Instant::now();
    let grammar_source = std::fs::read_to_string("src/grammar_c.txt").unwrap();
    let mut g = bnf_to_grammar(&grammar_source).unwrap();
    
    let mut precedence_list = vec!(
        (&["*", "/", "%"][..]),
        (&["+", "-"]),
        (&["<<", ">>"]),
        (&["<", "<=", ">", ">="]),
        (&["==", "!="]),
        (&["&"]),  (&["^"]),  (&["|"]),  (&["&&"]),  (&["||"]),
    );
    precedence_list.reverse();
    
    let mut prec_map = Vec::default();
    for (i, l) in precedence_list.iter().enumerate()
    {
        for s in *l
        {
            let index : u32 = string_cache_lookup(&mut g.string_cache, &mut g.string_cache_inv, *s).1;
            if index as usize >= prec_map.len()
            {
                prec_map.resize(index as usize + 1, 0);
            }
            prec_map[index as usize] = i as u32;
        }
    }
    
    println!("Boot time: {:?}", start.elapsed());
    
    println!("Loading: {input_fname}");
    let start = std::time::Instant::now();
    let test_source = std::fs::read_to_string(input_fname).unwrap();
    println!("Source text load time: {:?}", start.elapsed());
    
    let start = std::time::Instant::now();
    let tokens = tokenize(&mut g, &test_source);
    let tokens = tokens.unwrap();
    println!("Tokenization time: {:?} for {} tokens from {} bytes", start.elapsed(), tokens.len(), test_source.len());
    //let tokens = tokenize(&mut g, &"9152 6 3");

    //println!("{:#?}", &tokens[..tokens.len().min(10)]);
    
    let start = std::time::Instant::now();
    use std::rc::Rc;
    type HashMap<K, V> = std::collections::HashMap::<K, V, crate::HashBuilder>;
    type HashSet<V> = std::collections::HashSet::<V, crate::HashBuilder>;

    let mut hooks : HashMap<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], usize, &mut Vec<ASTNode>) -> Result<usize, String>>>
        = <_>::default();
    let mut guards = HashMap::<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], _) -> GuardResult>>::default();
    
    // FIXME: Okay using TypeId for this is actually a really bad idea, change it to ints.
    #[derive(Default, Debug)]
    struct MyData {
        typedef_stack : Vec<HashSet<u32>>,
        typedef_seen : HashSet<u32>,
        enum_stack : Vec<HashSet<u32>>,
        enum_seen : HashSet<u32>,
        variable_stack : Vec<HashSet<u32>>,
    }
    
    let type_specifier_checker : Rc<dyn Fn(&mut PrdGlobal, &[Token], usize) -> GuardResult>
        = Rc::new(|global : &mut PrdGlobal, tokens : &[Token], i : usize|
    {
        if i < tokens.len()
        {
            let nj = &tokens[i].text;
            //let n = &global.g.string_cache_inv[*nj as usize];
            let r = global.udata_r.entry(15238539).or_insert_with(|| RegexCacher::new(new_regex(
                r#"(?x)\A(?:typeof|__typeof__|void
                |__builtin_va_list|char|short|int|long|float|double|signed|unsigned|_Bool|_Complex|_Imaginary|_Float16|__bf16|__int128|const|volatile|__volatile__
                |enum|struct|union)\z"#
            ).unwrap()));
            if r.is_match_interned(*nj, &global.g.string_cache_inv)
            {
                //println!("!!!! accepting {n} as a type indicator");
                return GuardResult::Accept;
            }
            // FIXME: TODO: add an "ever seen set" optimization here too (like enums)
            let data = global.udata.get::<MyData>();
            let data = data.as_ref().unwrap();
            if data.typedef_seen.contains(nj)
            {
                for i in (0..data.typedef_stack.len()).rev()
                {
                    //println!("? checking {n} as a typedef");
                    if data.typedef_stack[i].contains(nj)
                    {
                        //println!("!!!! accepting {n} as a typedef");
                        return GuardResult::Accept;
                    }
                    if data.variable_stack[i].contains(nj)
                    {
                        //println!("!!!! nope that's a variable");
                        return GuardResult::Reject;
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
                let nj = &tokens[i].text;
                //let n = &global.g.string_cache_inv[*nj as usize];
                let r = global.udata_r.entry(75425463).or_insert_with(|| RegexCacher::new(new_regex(
                    r#"(?x)\A(?:typeof|__typeof__|typedef|extern
                    |__builtin_va_list|static|auto|register|const|restrict
                    |__cdecl|__stdcall
                    |__restrict__|volatile|__volatile__|__inline__|__inline|inline|void|char|short
                    |int|long|float|double|signed|unsigned|_Bool|_Complex|_Imaginary|_Float16|__bf16|__int128|enum|struct|union)\z"#
                ).unwrap()));
                if r.is_match_interned(*nj, &global.g.string_cache_inv)
                {
                    //println!("!!!! accepting {n} as a declaration indicator");
                    return GuardResult::Accept;
                }
                // FIXME: TODO: add an "ever seen set" optimization here too (like enums)
                let data = global.udata.get::<MyData>();
                let data = data.as_ref().unwrap();
                //println!("? checking {n} as ever being a typedef");
                if data.typedef_seen.contains(nj)
                {
                    //println!("? yep");
                    for i in (0..data.typedef_stack.len()).rev()
                    {
                        //println!("? checking {n} as a typedef");
                        if data.typedef_stack[i].contains(nj)
                        {
                            //println!("!!!! accepting {n} as a typedef");
                            return GuardResult::Accept;
                        }
                        if data.variable_stack[i].contains(nj)
                        {
                            //println!("!!!! nope that's a variable");
                            return GuardResult::Reject;
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
                let nj = &tokens[i].text;
                let n = &global.g.string_cache_inv[*nj as usize];
                if &**n == "case" { return GuardResult::Accept; }
                let nj2 = &tokens[i+1].text;
                let n2 = &global.g.string_cache_inv[*nj2 as usize];
                let r = global.udata_r.entry(648245613).or_insert_with(|| RegexCacher::new(new_regex(
                    r#"^(?:[a-zA-Z_]|(?:\\u[a-fA-F0-9]{1,4}|\\U[a-fA-F0-9]{1,8}))(?:[a-zA-Z_]|(?:\\u[a-fA-F0-9]{1,4}|\\U[a-fA-F0-9]{1,8})|[0-9])*$"#
                ).unwrap()));
                if &**n2 == ":" && r.is_match_interned(*nj, &global.g.string_cache_inv)
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
                let n = &global.g.string_cache_inv[*n as usize];
                if &**n == "("
                {
                    if !matches!(f(global, tokens, i+1), GuardResult::Accept)
                    {
                        //println!("rejecting cast at {i} (type specifier check failed)");
                        return GuardResult::Reject;
                    }
                    let i2 = i.strict_add_signed(tokens[i].pair);
                    let i3 = i2 + 1;
                    if i3 < tokens.len()
                    {
                        let n2 = &global.g.string_cache_inv[tokens[i3].text as usize];
                        if &**n2 == "{"
                        {
                            //println!("rejecting cast at {i} (it's a struct literal)");
                            return GuardResult::Reject;
                        }
                    }
                    //println!("accepting cast at {i}");
                    return GuardResult::Accept;
                }
            }
            //println!("rejecting cast at {i}");
            GuardResult::Reject
        }
    ));
    let f = Rc::clone(&type_specifier_checker);
    guards.insert("is_postfix_not_sizeof_argument".to_string(),
        Rc::new(move |global : &mut PrdGlobal, tokens : &[Token], i : usize|
        {
            if i < tokens.len()
            {
                let n = &tokens[i].text;
                let n = &global.g.string_cache_inv[*n as usize];
                if &**n == "("
                {
                    if !matches!(f(global, tokens, i+1), GuardResult::Accept)
                    {
                        //println!("rejecting cast at {i} (type specifier check failed)");
                        return GuardResult::Accept;
                    }
                    let i2 = i.strict_add_signed(tokens[i].pair);
                    let i3 = i2 + 1;
                    if i3 < tokens.len()
                    {
                        let n2 = &global.g.string_cache_inv[tokens[i3].text as usize];
                        if matches!(&***n2, "{" | "(" | "++" | "--" | "." | "->")
                        {
                            //println!("rejecting cast at {i} (it's a struct literal)");
                            return GuardResult::Accept;
                        }
                    }
                    //println!("accepting cast at {i}");
                    return GuardResult::Reject;
                }
            }
            //println!("rejecting cast at {i}");
            GuardResult::Reject
        }
    ));
    
    guards.insert("is_ident_not_known_enum".to_string(),
        Rc::new(|global : &mut PrdGlobal, tokens : &[Token], i : usize|
        {
            if i < tokens.len()
            {
                let nj = &tokens[i].text;
                let r = global.udata_r.entry(648245613).or_insert_with(|| RegexCacher::new(new_regex(
                    r#"^(?:[a-zA-Z_]|(?:\\u[a-fA-F0-9]{1,4}|\\U[a-fA-F0-9]{1,8}))(?:[a-zA-Z_]|(?:\\u[a-fA-F0-9]{1,4}|\\U[a-fA-F0-9]{1,8})|[0-9])*$"#
                ).unwrap()));
                if r.is_match_interned(*nj, &global.g.string_cache_inv)
                {
                    let mut data = global.udata.get_mut::<MyData>();
                    let data = data.as_mut().unwrap();
                    if data.enum_seen.contains(nj)
                    {
                        for s in data.enum_stack.iter()
                        {
                            if s.contains(nj)
                            {
                                return GuardResult::Reject;
                            }
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
                let nj = &tokens[i].text;
                let mut data = global.udata.get_mut::<MyData>();
                let data = data.as_mut().unwrap();
                
                if data.enum_seen.contains(nj)
                {
                    for s in data.enum_stack.iter()
                    {
                        if s.contains(nj)
                        {
                            return GuardResult::Accept;
                        }
                    }
                }
            }
            GuardResult::Reject
        }
    ));
    
    hooks.insert("init".to_string(),
        Rc::new(|global : &mut PrdGlobal, _tokens : &[Token], _i : usize, _children : &mut Vec<ASTNode>|
        {
            let mut data = MyData::default();
            data.typedef_stack.push(<_>::default());
            data.variable_stack.push(<_>::default());
            data.enum_stack.push(<_>::default());
            global.udata.insert(data);
            Ok(0)
        }
    ));
    
    hooks.insert("scope_push".to_string(),
        Rc::new(|global : &mut PrdGlobal, _tokens : &[Token], _i : usize, _children : &mut Vec<ASTNode>|
        {
            let mut data = global.udata.get_mut::<MyData>();
            let data = data.as_mut().unwrap();
            data.typedef_stack.push(<_>::default());
            data.variable_stack.push(<_>::default());
            data.enum_stack.push(<_>::default());
            Ok(0)
        }
    ));
    hooks.insert("scope_pop".to_string(),
        Rc::new(|global : &mut PrdGlobal, _tokens : &[Token], _i : usize, _children : &mut Vec<ASTNode>|
        {
            let mut data = global.udata.get_mut::<MyData>();
            let data = data.as_mut().unwrap();
            data.typedef_stack.pop();
            data.variable_stack.pop();
            data.enum_stack.pop();
            Ok(0)
        }
    ));
    
    // FIXME: URGENT: log enums too!!!!
    hooks.insert("typedefs_log".to_string(),
        Rc::new(|global : &mut PrdGlobal, _tokens : &[Token], _i : usize, children : &mut Vec<ASTNode>|
        {
            let mut data = global.udata.get_mut::<MyData>();
            let data = data.as_mut().unwrap();
            let mut is_typedef = false;
            let f : &mut dyn FnMut(&ASTNode) -> bool = &mut |c : &ASTNode|
            {
                let n = &global.g.string_cache_inv[c.text as usize];
                if c.children.is_none() && &**n == "typedef" { is_typedef = true; }
                if c.children.is_some() && matches!(&***n, "typedef_name" | "parameter_type_list" | "struct_or_union_specifier" | "enum_specifier") { return false; }
                true
            };
            for c in children.iter_mut()
            {
                visit_ast(c, f);
                //print_ast_pred_recdec(c, &global.g.string_cache_inv, 0);
            }
            
            //println!("looking for typedef storeability at {_i}. might be typedef? {is_typedef}");
            //println!("found typedef context to log with");
            let f2 : &mut dyn FnMut(&ASTNode) -> bool = &mut |c : &ASTNode|
            {
                let n = &global.g.string_cache_inv[c.text as usize];
                if c.children.is_some() && &**n == "identifier"
                {
                    let nj2 = c.children.as_ref().unwrap()[0].text;
                    
                    if is_typedef
                    {
                        //println!("found. {is_typedef}");
                        data.typedef_stack.last_mut().unwrap().insert(nj2);
                        data.typedef_seen.insert(nj2);
                    }
                    else
                    {
                        //println!("found. {is_typedef}");
                        data.variable_stack.last_mut().unwrap().insert(nj2);
                    }
                    //println!("logged {} as typedef", global.g.string_cache_inv[c.children.as_ref().unwrap()[0].text as usize]);
                }
                if c.children.is_some() && matches!(&***n, "typedef_name" | "parameter_type_list" | "struct_or_union_specifier" | "enum_specifier") { return false; }
                true
            };
            for c in children.iter_mut()
            {
                visit_ast(c, f2);
            }
            //println!("-------");
            Ok(0)
        }
    ));
    hooks.insert("enums_log".to_string(),
        Rc::new(|global : &mut PrdGlobal, _tokens : &[Token], _i : usize, children : &mut Vec<ASTNode>|
        {
            //println!("----");
            let mut data = global.udata.get_mut::<MyData>();
            let data = data.as_mut().unwrap();
            let f : &mut dyn FnMut(&ASTNode) -> bool = &mut |c : &ASTNode|
            {
                let n = &global.g.string_cache_inv[c.text as usize];
                if c.children.is_some() && &**n == "enumeration_constant"
                {
                    let nj2 = c.children.as_ref().unwrap()[0].children.as_ref().unwrap()[0].text;
                    if let Some(s) = data.enum_stack.last_mut()
                    {
                        s.insert(nj2);
                    }
                    data.enum_seen.insert(nj2);
                }
                true
            };
            
            for c in children.iter_mut()
            {
                visit_ast(c, f);
            }
            //println!("-------");
            Ok(0)
        }
    ));
    
    hooks.insert("fix_infix_precedence".to_string(),
        Rc::new(move |_global : &mut PrdGlobal, _tokens : &[Token], mut _i : usize, children : &mut Vec<ASTNode>|
        {
            if children.len() <= 3 { return Ok(0); }
            let default_text = *_global.g.string_cache.get("infix_expression").unwrap();
            
            fn parse_expression_impl(default_text : u32, prec_map : &[u32], items : &mut Vec<ASTNode>, mut lhs : ASTNode, min_precedence : u32) -> ASTNode
            {
                while items.len() > 1 && prec_map[items.last().unwrap().text as usize] >= min_precedence
                {
                    let op = items.pop().unwrap();
                    let mut rhs = items.pop().unwrap();
                    while items.len() > 1 && prec_map[items.last().unwrap().text as usize] > prec_map[op.text as usize]
                    {
                        rhs = parse_expression_impl(default_text, prec_map, items, rhs, prec_map[op.text as usize] + 1);
                    }
                    if lhs.children.is_none() || lhs.children.as_ref().unwrap().len() == 1
                    {
                        let new_children_list = vec!(lhs, op, rhs);
                        let count = new_children_list.iter().map(|x| x.token_count).sum();
                        lhs = ASTNode::new(Some(new_children_list), default_text, count, );
                    }
                    else if let Some(c) = lhs.children.as_mut()
                    {
                        c.push(op);
                        c.push(rhs);
                    }
                }
                lhs
            }
            fn parse_expression(default_text : u32, prec_map : &[u32], items : &mut Vec<ASTNode>) -> ASTNode
            {
                items.reverse();
                let n = items.pop().unwrap();
                parse_expression_impl(default_text, prec_map, items, n, 0)
            }
            
            let new_node = parse_expression(default_text, &prec_map, children);
            std::mem::swap(children, &mut new_node.children.unwrap());
            
            Ok(0)
        }
    ));
    
    hooks.insert("entered_function".to_string(),
        Rc::new(move |global : &mut PrdGlobal, _tokens : &[Token], mut _i : usize, children : &mut Vec<ASTNode>|
        {
            let mut data = global.udata.get_mut::<MyData>();
            let data = data.as_mut().unwrap();
            
            for c in children.iter_mut()
            {
                let n : &Rc<String> = &global.g.string_cache_inv[c.text as usize];
                if c.children.is_some() && &**n == "declarator"
                {
                    //print_ast_pred_recdec(c, &global.g.string_cache_inv, 0);
                    let mut yet_valid = false;
                    for c in c.children.as_mut().unwrap().iter_mut()
                    {
                        let f : &mut dyn FnMut(&ASTNode) -> bool = &mut |c : &ASTNode|
                        {
                            let n = &global.g.string_cache_inv[c.text as usize];
                            if !yet_valid && c.children.is_some() && &**n == "parameter_type_list"
                            {
                                //println!(":::::FSGA#$GO#$L^@!^%151515:asdfgkjaergioaerg");
                                yet_valid = true;
                                return true;
                            }
                            if yet_valid && c.children.is_some() && &**n == "identifier"
                            {
                                let nj2 = c.children.as_ref().unwrap()[0].text;
                                data.variable_stack.last_mut().unwrap().insert(nj2);
                                //let n2 : &Rc<String> = &global.g.string_cache_inv[nj2 as usize];
                                //println!("--- found var {n2}");
                                return false;
                            }
                            if c.children.is_some() && matches!(&***n, "typedef_name" | "parameter_type_list" | "struct_or_union_specifier")
                            {
                                return false;
                            }
                            true
                        };
                        visit_ast(c, f);
                    }
                    
                    // ????
                }
            }
            
            //println!("{:?}", data);
            Ok(0)
        }
    ));
    
    let hooks = Rc::new(hooks);
    let guards = Rc::new(guards);
    
    let ast = parse(&g, "S", &tokens[..], guards, hooks);
    println!("{}", ast.is_ok());
    println!("Parse time taken: {:?} under {} items", start.elapsed(), tokens.len());
    let start = std::time::Instant::now();
    {
        //if let Ok(ast) = &ast { print_ast_pred_recdec(ast, &g.string_cache_inv, 0); }
    }
    drop(ast.unwrap());
    println!("AST destruction time: {:?}", start.elapsed());
    println!("sizeof ASTNode {}", std::mem::size_of::<ASTNode>());
}
