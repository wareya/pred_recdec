use mimalloc::MiMalloc;
#[global_allocator]
static GLOBAL: MiMalloc = MiMalloc;

pub use rustc_hash::FxBuildHasher as HashBuilder;

mod bnf;
use bnf::*;

mod ast;
use ast::*;

mod json;
mod c;

fn main() {
    let grammar_source = r#"
S ::= @peek(0, "(") parenexpr
parenexpr ::=
    @peek(1, ")") "(" ")" $pruned
    | "(" $become itemlist $pruned
itemlist ::=
    @peek(0, ")") $pruned ")"
    | @peek(0, "(") parenexpr $become itemlist
    | @auto r`[a-zA-Z_][a-zA-Z_0-9]*|[0-9\.]*`r $become itemlist
    "#;
    let mut g = bnf_to_grammar(&grammar_source).unwrap();
    
    let test_source = r#"
    (a b (q x)kfwaiei i  9 (af0f1a) () () )
    "#;
    
    let tokens = tokenize(&mut g, &test_source);
    let tokens = tokens.unwrap();
    
    use std::rc::Rc;
    let ast = parse(&g, "S", &tokens[..], Rc::new(<_>::default()), Rc::new(<_>::default()));
    
    if let Ok(ast) = &ast
    {
        print_ast_pred_recdec(ast, &g.string_cache_inv, 0);
        
        // Prints:
        /*
            S {
             parenexpr {
              a
              b
              parenexpr {
               q
               x
              };
              kfwaiei
              i
              9
              parenexpr {
               af0f1a
              };
              parenexpr {
              };
              parenexpr {
              };
             };
            };
        */
    }
    drop(ast.unwrap());
    
    /*
    let grammar_source = r#"
S ::= @peek(0, "(") parenexpr
parenexpr ::=
    @peek(1, ")") "(" ")" $pruned
    | "(" $become itemlist $pruned
itemlist ::=
    @peek(0, ")") $pruned ")"
    | @peek(0, "(") parenexpr $become itemlist
    | @auto r`[a-zA-Z_][a-zA-Z_0-9]*|[0-9\.]*`r $become itemlist
    "#;
    */
}
