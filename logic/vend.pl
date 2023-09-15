:- dynamic(product/3).

% Define available products, prices, and initial stock

product('Coke', 1, 5).
product('Chips', 2, 10).
product('Water', 1, 20).

% Vend the product
vend(Product, Payment) :- 
    product(Product, Price, Stock),
    Stock > 0,
    Payment >= Price,
    NewStock is Stock - 1,
    retract(product(Product, Price, Stock)),
    asserta(product(Product, Price, NewStock)),
    Change is Payment - Price,
    format("Vending ~w. Your change is ~w.", [Product, Change]).

% If stock is zero
vend(Product, _) :-
    product(Product, _, Stock),
    Stock =:= 0,
    format("Sorry, ~w is out of stock.", [Product]).

% If insufficient payment
vend(Product, Payment) :-
    product(Product, Price, _),
    Payment < Price,
    format("Insufficient payment for ~w.", [Product]).

% If product does not exist
vend(Product, _) :-
    \+ product(Product, _, _),
    format("The product ~w does not exist.", [Product]).
