mod bnf;
use bnf::*;

mod earley;
#[allow(unused)]
use earley::*;

mod packrat;
#[allow(unused)]
use packrat::*;

mod brute_force;
#[allow(unused)]
use brute_force::*;

mod pred_recdec;
#[allow(unused)]
use pred_recdec::*;

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
/*
    let s = r####"
S ::= B | A
A ::= "a" A | "a"
B ::= "z" | "a" B | "a"
"####;
*/
/*
    let s = r####"
S ::= AX S | AX
AX ::= A "x"
A ::= A A | "a"
B ::= "b"
"####;
*/
/*
    let s = r####"
S ::= C
A ::= "iftrue" C | expr
B ::= "iftrue" C "else" C | expr
C ::= "iftrue" C "else" C | "iftrue" C | expr
expr ::= rx%[0-9]+%rx
"####;
*/
/*
    let s = r####"
S ::= statement
statement ::= "PEEK 0 if" ifcond | expr ";"
ifcond ::= "if" expr block else_maybe
else_maybe ::= "PEEK 0 else" "else" block | #intentionally empty
expr ::= 
    "PEEK 0 true" "true"
    | "PEEK 0 false" "false"
    | rx%[0-9]+%rx
block ::= "PEEK 0 {" "{" statement "}" | statement
"####;
*/

    let s = r####"
S ::= expr5
expr5 ::= expr0 "$BECOME" expr5_tail
expr5_tail ::=
    "PEEK 0 *" "*" expr0 "$BECOME" expr5_tail
    | #intentionally empty
expr0 ::= rx%[0-9]+%rx
"####;
    let mut g = bnf_to_grammar(&s).unwrap();
    println!("{:#?}", &g);
    
    //let tokens = tokenize(&mut g, &"a a a a a a a a a a   \n".repeat(10000));
    //let tokens = tokenize(&mut g, &"if 1 then if 325 then 1953 else 15\n");
    //let tokens = tokenize(&mut g, &"a a a a a a x");
    //let tokens = tokenize(&mut g, &"iftrue iftrue 555 else 555");
    //let tokens = tokenize(&mut g, &"if true true;");
    let tokens = tokenize(&mut g, &"5 * 2 * 5 * 1 * 2 * 9153");

    //println!("{:#?}", tokens);
    
    let tokens = tokens.unwrap();
    
    let start = std::time::Instant::now();
    //println!("{:#?}", earley_recognize(&g, "S", &tokens[..]));
    //let ast = earley_parse(&g, "S", &tokens[..]);
    //let ast = packrat_parse(&g, "S", &tokens[..]);
    //let ast = brute_force_parse(&g, "S", &tokens[..]);
    let ast = pred_recdec_force_parse(&g, "S", &tokens[..]);
    //println!("{}", ast.is_ok());
    println!("Time taken: {:?} under {} items", start.elapsed(), tokens.len());
    //let ast = ast.unwrap();
    //println!("{:#?} {} {} {} {}", ast, ast.text, ast.children.as_ref().unwrap().len(), ast.token_start, ast.token_count);
    //print_ast_earley(&ast.unwrap(), 0);
    //print_ast_packrat(&ast.unwrap(), 0);
    //print_ast_brute_force(&ast.unwrap(), 0);
    print_ast_pred_recdec(&ast.unwrap(), 0);
}
