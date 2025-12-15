mod bnf;
use bnf::*;

mod earley;
use earley::*;

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
    let s = r####"
program ::= S
S ::= A A "c"
A ::= #intentionally empty
"####;
    let g = bnf_to_grammar(&s).unwrap();
    println!("{:#?}", &g);
    
    let tokens = tokenize(&g, "c");
    println!("{:#?}", tokens);
    
    let tokens = tokens.unwrap();
    
    println!("{:#?}", earley_recognize(&g, "program", &tokens[..]));
}
