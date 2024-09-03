To build: clang++ -std=c++23 -g main.cpp -o rustgen.exe
It will ask you a couple questions, char or int or all, then will ask for a filename to pipe the results to.
For example, do a "cargo new test_codegen". Then when you are prompted give the fullpath to ./test_codegen/src/main.rs.
Keep in mind it will overwrite what you might have in ./test_codegen/src/main.rs so you might just pipe it local to 
rustgen.exe to a temp.rs.
If you are on Windows, specify the fullpath the double backwhacks.  "E:\\new_repo\\test_rust_gen\\src\\main.rs". 
Forward whacks might work too.  This is sort of a prototype for a fuller featured web app.
