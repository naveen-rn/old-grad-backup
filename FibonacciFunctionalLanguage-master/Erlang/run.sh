erl -compile fibonacci;
erl -noshell -s fibonacci printTests -s init stop; 
rm -rf *.beam