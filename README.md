# fibin language
A simple functional language written using c++ templates.

--- 
coauthor: [@Pawel494](https://github.com/Pawel494)

# Semantics
* Literals `Lit` - only allowed Fibbonaci numbers (non negative): `Fib<0> = 0, Fib<1> = 1 ...`
  or logic values: `True, False`, \
  example: 
  ```
  Lit<Fib<0>>, Lit<True>
  ```
  
* Variables `Var`:
  ```
  Var(const char*)
  ```
  labels are string (1 to 6 signs) with letters (case insensitive) and digits, \
  example:
  ```
  Var("A"), Var("01234"), Var("Cdefg")
  ```
  
* Arithmetic operations `Sum, Inc1, Inc10`
    - `Sum<...>` - multiple arguments sum (at least two),
    - `Inc1<Arg>` - adds `Fib<1>` to `Arg`,
    - `Inc10<Arg>` - adds `Fib<10` to `Arg`,
 
  example:
  ```
  Sum<Lit<Fib<0>>, Lit<Fib<1>>, Lit<Fib<3>>>, Inc1<Lit<Fib<0>>>
  ```
 
* Comparison `Eq` - 
  `Eq<Left, Right>` compares value of Left with Right, \
  example: 
  ```
  Eq<Lit<Fib<0>>, Lit<Fib<1>>>
  ```
  
* Refernce `Ref` - 
  `Ref<Var>` return the value of `Var`, \
  example:
  ```
  Ref<Var("A")>
  ```
  
* Expression `Let` -
  `Let<Var, Value, Expression>` assigns `Value` to the `Var` and calculates given `Expression`, \
  example: 
  ```
  Let<Var("A"), Lit<Fib<1>>, Ref<Var("A")>>
  ```
  
* Expression `If` -
  `If<Condition, Then, Else>` if `Condition` result is True then calculates value of `Then` otherwise value of `Else` is calculated, \ 
  example: 
  ```
  If<Lit<True>, Lit<Fib<1>>, Lit<Fib<0>>>
  ```
  
* Expression `Lambda` -
  `Lambda<Var, Body>` reprezents anonymous function with singe input argument `Var` and body `Body`, \
  example: 
  ```
  Lambda<Var("x"), Ref<Var("x")>>
  ```
  
* Function invocation `Invoke` -
  `Invoke<Fun, Param>` calculates `Fun` result for the given input parameter `Param`, \
  example: 
  ```
  Invoke<Lambda<Var("x"), Ref<Var("x")>>, Lit<Fib<0>>>
  ```
