

#[cfg(test)]
mod tests {
    use crate::bnf::*;
    use crate::ast::*;
    use std::fs;

    #[test]
    fn test_perf() {
        let grammar_source = std::fs::read_to_string("src/grammar_json.txt").unwrap();
        println!("Loading grammar...");
        let mut g = bnf_to_grammar(&grammar_source).unwrap();
        println!("Loaded.");
        
        use std::rc::Rc;
        type HashMap<K, V> = std::collections::HashMap::<K, V, crate::HashBuilder>;

        let hooks : HashMap<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], usize, &mut Vec<ASTNode>) -> Result<usize, String>>>
            = <_>::default();
        let guards = HashMap::<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], _) -> GuardResult>>::default();
        
        let hooks = Rc::new(hooks);
        let guards = Rc::new(guards);
        
        let content_maybe = fs::read_to_string("json_bench/citm_catalog.json");
        if content_maybe.is_err()
        {
            panic!("Please copy https://github.com/miloyip/nativejson-benchmark/blob/master/data/citm_catalog.json into the json_bench/ folder to run JSON performance tests.")
        }
        
        let content = content_maybe.unwrap();
        
        let start = std::time::Instant::now();
        let start2 = std::time::Instant::now();
        let tokens = tokenize(&mut g, &content).unwrap();
        println!("Tokenize time: {:?}", start2.elapsed());
        
        let start2 = std::time::Instant::now();
        parse(&g, "json", &tokens[..], guards.clone(), hooks.clone()).unwrap();
        println!("Parse time: {:?}", start2.elapsed());
        println!("Total time: {:?}", start.elapsed());
        
        let mut d = content.as_bytes().to_vec();
        
        let start = std::time::Instant::now();
        let _v = simd_json::to_owned_value(&mut d).unwrap();
        println!("simdjson time: {:?}", start.elapsed());
        
        let start = std::time::Instant::now();
        let _v : serde_json::Value = serde_json::from_str(&content).unwrap();
        //drop(content);
        println!("serde_json time: {:?}", start.elapsed());
        //println!("{:?}", _v);
    }

    #[test]
    fn test() {
        let grammar_source = std::fs::read_to_string("src/grammar_json.txt").unwrap();
        let mut g = bnf_to_grammar(&grammar_source).unwrap();
        
        use std::rc::Rc;
        type HashMap<K, V> = std::collections::HashMap::<K, V, crate::HashBuilder>;

        let hooks : HashMap<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], usize, &mut Vec<ASTNode>) -> Result<usize, String>>>
            = <_>::default();
        let guards = HashMap::<String, Rc<dyn Fn(&mut PrdGlobal, &[Token], _) -> GuardResult>>::default();
        
        let hooks = Rc::new(hooks);
        let guards = Rc::new(guards);
        
        let mut n = 0;
        for entry in fs::read_dir("json_tests").unwrap()
        {
            n += 1;
            let entry = entry.unwrap();
            let path = entry.path();
            if path.is_file()
            {
                println!("testing {}...", path.display());
                let content_maybe = fs::read_to_string(&path);
                let mut ok_simd = false;
                let mut ok_serde = false;
                let is_ok = if let Ok(content) = content_maybe
                {
                    let mut attempt_parse = |content : &str| -> Result<ASTNode, String>
                    {
                        let mut d = content.as_bytes().to_vec();
                        let _v = simd_json::to_owned_value(&mut d);
                        let _v2 : Result<serde_json::Value, _> = serde_json::from_str(&content);
                        ok_simd = _v.is_ok();
                        ok_serde = _v2.is_ok();
                        
                        let tokens = tokenize(&mut g, content)?;
                        parse(&g, "json", &tokens[..], guards.clone(), hooks.clone())
                    };
                    
                    //println!("byte count {}", content.len());
                    let ast = attempt_parse(&content);
                    /*
                    if let Ok(ast) = &ast
                    {
                        print_ast_pred_recdec(ast, &g.string_cache_inv, 0);
                    }
                    */
                    ast.is_ok()
                }
                else
                {
                    false
                };
                //println!(" -> {}", is_ok);
                let fname = path.file_name().unwrap().to_str().unwrap().to_string();
                if fname.starts_with("i_") { continue; }
                if fname.starts_with("y_") { assert!(is_ok); }
                if fname.starts_with("n_") { assert!(!is_ok); }
                if is_ok != ok_simd { println!("---- INFO: simdjson is wrong"); }
                if is_ok != ok_serde { println!("---- INFO: serde_jsoin is wrong"); }
            }
        }
        if n < 10
        {
            panic!("Please copy the complete contents of https://github.com/nst/JSONTestSuite/tree/master/test_parsing into the json_tests/ folder to run JSON parser tests.")
        }
    }
}