mod bnf;
use bnf::*;

mod earley;
#[allow(unused)]
use earley::*;

mod packrat;
#[allow(unused)]
use packrat::*;

// Removed the main function as it was extraneous.
fn main() {
    /*
    let s = r####"
program ::= statement_list
statement_list ::= statement_list statement | statement
statement ::= declaration | command | assignment

declaration ::= "var" identifier

command ::= command_name expr | command_name
command_name ::= "print" | "exit"

assignment ::= identifier "=" expr
expr ::= binexpr_0
binexpr_0 ::= binexpr_0 binop_0 binexpr_1 | binexpr_1
binop_0 ::= "+" | "-"
binexpr_1 ::= binexpr_1 binop_1 core_expr | core_expr
binop_1 ::= "*" | "/"
core_expr ::= identifier | number

identifier ::= rx%[a-zA-Z_][a-zA-Z_0-9]*%rx
number ::= rx%[0-9]+(\.[0-9]+)?%rx
"####;
*/
/*
    let s = r####"
program ::= A A "a"
A ::= #intentionally empty
"####;
*/
/*
    let s = r####"
S ::= A
#A ::= "a" A | "a" # packrat's preference
A ::= A "a" | "a" # earley's preference
"####;
*/
/*
    let s = r####"
S ::= expr
expr ::= if | num
if ::= "if" expr "then" expr "else" expr | "if" expr "then" expr
num ::= rx%[0-9]+%rx
"####;
*/
    let s = r####"
S ::= B | A
A ::= "a" A | "a"
B ::= "z" | "a" B | "a"
"####;
    let mut g = bnf_to_grammar(&s).unwrap();
    println!("{:#?}", &g);
    
    //let tokens = tokenize(&mut g, &"a a a a a a a a a a   \n".repeat(10000));
    //let tokens = tokenize(&mut g, &"if 1 then if 325 then 1953 else 15\n");
    let tokens = tokenize(&mut g, &"a a a a a");

    //println!("{:#?}", tokens);
    
    let tokens = tokens.unwrap();
    
    let start = std::time::Instant::now();
    //println!("{:#?}", earley_recognize(&g, "S", &tokens[..]));
    //let ast = earley_parse(&g, "S", &tokens[..]);
    let ast = packrat_parse(&g, "S", &tokens[..]);
    //println!("{}", ast.is_ok());
    println!("Time taken: {:?} under {} items", start.elapsed(), tokens.len());
    //let ast = ast.unwrap();
    //println!("{:#?} {} {} {} {}", ast, ast.text, ast.children.as_ref().unwrap().len(), ast.token_start, ast.token_count);
    //print_ast_earley(&ast.unwrap(), 0);
    print_ast_packrat(&ast.unwrap(), 0);
}
