-module(fibonacci).
-compile(export_all).

fibCalcRecursive(Position) 
	when Position =< 0 ->[];
fibCalcRecursive(1) -> [1];
fibCalcRecursive(Position) -> fibCalcRecursive(Position, [1,1]).
    
fibCalcRecursive(Position, FibList)
	when Position == length(FibList) -> FibList;
fibCalcRecursive(Position, FibList) ->
    fibCalcRecursive(Position, FibList ++ 
		[lists:nth(length(FibList), FibList) + lists:nth(length(FibList) -1, FibList)]). 	

fibCalcImmutable(Position)
	when Position =< 0 ->[];
fibCalcImmutable(1) -> [1];
fibCalcImmutable(Position) ->
   lists:foldl(
	fun(_, Accum) ->  
		   Accum ++ [lists:nth(length(Accum), Accum) + lists:nth(length(Accum)-1, Accum)]
	end, [1,1], createList(Position-2)).

createList(Position)
	when Position =< 0 ->[];
createList(Position) -> [1] ++ createList(Position-1).

printTests() ->
	io:format("Recursive ~n"),
	io:format("-1 : ~p~n", [fibCalcRecursive(-1)]),
	io:format("0 : ~p~n", [fibCalcRecursive(0)]),
	io:format("1 : ~p~n", [fibCalcRecursive(1)]),
	io:format("2 : ~p~n", [fibCalcRecursive(2)]),
	io:format("4 : ~p~n", [fibCalcRecursive(4)]),
	io:format("6 : ~p~n", [fibCalcRecursive(6)]),
	io:format("~nImmutable ~n"),
	io:format("-1 : ~p~n", [fibCalcImmutable(-1)]),
	io:format("0 : ~p~n", [fibCalcImmutable(0)]),
	io:format("1 : ~p~n", [fibCalcImmutable(1)]),
	io:format("2 : ~p~n", [fibCalcImmutable(2)]),
	io:format("4 : ~p~n", [fibCalcImmutable(4)]),
	io:format("6 : ~p~n", [fibCalcImmutable(6)]).
