#### 为类型取别名Swift Tips:



###### 1. 元组

* 元组允许一些并不相关的类型进行自由组合成为新的集合类型

  ``` 
  var pen:(name:String, price:Int) = ("钢笔",1)
  print(pen.name)
  print(pen.price)
  ```

* 在创建元组时，也可以不指定元组中参数的名称，元组会自动为每个参数分配下标，下标值将从0开始依次递增。

  ```
  var car:(String, Int) = ("BMW", 100086)
  print(car.0)
  print(car.1)
  ```

* 元组实例被创建后，可以通过指定的变量或者常量来分解它:

  ~~~
  var (theName, thePrice) = car
  print(theName)
  print(thePrice)
  ~~~

* 有些时候，开发者可能并不需要获取某个元组实例中所有元素的值，这种情况下，开发者也可以将某些不需要获取的元素使用匿名的方式来接收

  ```
  var (name,_) = car
  print(name)
  ```

* 在Swift语言中，常常使用符号“_”来表示匿名的概念，因此“_”也被称为匿名标识符。

* 元组虽然使用起来十分方便，然而其只适用于简单数据的组合，对于结构复杂的数据，要采用结构体或者类来实现。

  

###### 2. 可选值类型

* 在Swift语言中普通的类型是不允许为nil的，如果一个变量在逻辑上可能为nil，则开发者需要将其包装为Optional类型。

  ~~~
  var obj: String?
  if(obj == nil){
      print("aaa")
  }
  ~~~

* Optional类型不会独立存在，其总是会附着于某个具体的数据类型之上，具体的数据类型可以是基本数据类型，可以是结构体，也可以是类等。

* 如果其附着类型对应的量值有具体的值，则其为具体值的包装。

* 如果其附着类型对应的量值没有具体的值，则其为nil。

* Optional类型中的nil读者也可以理解为一种值。

* Optional类型是对普通类型的一种包装，因此在使用的时候也需要对其进行拆包操作，拆包将使用到Swift中的操作符“! ”。

  ~~~
  var obj: String? = "HS"
  if(obj != nil){
      print(obj!)
  }
  ~~~

* 在使用“! ”进行Optional值的拆包操作时，必须保证要拆包的值不为nil，否则程序运行会出错。

* Swift语言还提供了一种if-let语法结构来进行Optional类型值的绑定操作

  ```
  if let tmp = obj {
      print(tmp)
  }else{
      obj = "Lucy" 
      print(obj!)
  }
  ```

* 上面的代码可以这样理解：如果obj有值，则if-let结构将创建一个临时常量tmp来接收obj拆包后的值，并且执行if为真时所对应的代码块，在执行的代码块中，开发者可以直接使用拆包后的obj值tmp。如果obj为nil，则会进入if为假的代码块中，开发者可以在else代码块中将obj重新赋值使用。

* if-let结构中也可以同时进行多个Optional类型值的绑定，之间用逗号隔开

  ```
  var obj1:Int? = 1, obj2:Int? = 2
  if let tmp1 = obj1,let tmp2 = obj2{
      print(tmp1,tmp2)
  }
  ```

* 在同时进行多个Optional类型值的绑定时，只有所有Optional值都不为nil，绑定才会成功，代码执行才会进入if为真的代码块中。

##### 

###### 3. 为类型取别名

* Swift语言中使用typealias关键字来为某个类型取一个别名

  ```
  typealias Price = Int
  var penPrice:Price = 10 
  ```

* 灵活使用typealias为类型取别名可以优化代码的可读性。 



###### 4.字符串组合

* Swift中的Sring类型对“+”运算符进行了重载实现，即开发者可以直接使用“+”符号将多个字符串组合拼接为新的字符串。

  ```
  var c1 = "Hello"
  var c2 = "World"
  var c3 = c1 + " " + c2
  ```

*  除了可以使用格式化的构造方法外，Swift中还提供了一种十分方便的字符串插值方法，示例如下：

  ```
  var d = "Hello \(c2)"
  ```

*  “\()”结构可以将其他数据类型转换为字符串类型并且插入字符串数据的相应位置。



###### 5.空合并运算符

* 空合并运算符是针对可选类型而设计的运算符。

  ```
  var q: Int? = 8
  var value:Int
  if q != nil{
      value = q!
  }else{
      value = 0
  }
  ```

  上述代码等价于：

  ```
  var q:Int? = 8
  var value:Int
  value = q ?? 0
  ```

* 空合并运算符“? ? ”是一个二元运算符。
* 其需要两个操作数，第一个操作数必须为一个Optional值，如果此Optional值不为nil，则将其进行拆包操作，并作为空合并运算的运算结果。如果此Optional值为nil，则会将第二个操作数作为空合并操作运算的结果返回。



###### 6.区间运算符

* Swift提供了一个区间运算符来快捷直观地表示范围区间。

  ```
  //创建范围 >=0 且 <=10 的闭区间
  var range1 = 0...10
  
  //创建范围 >=0 且 <10 的半开区间
  var range2 = 0..<10
  ```

* 也可以通过“~=”运算符来检查某个数字是否包含于范围中

  ```
  //8是否在range1中
  print(range1~=8)
  ```

  ```
  for index in 1...5 {
      print(index)
  }
  ```

* Swift中使用“_”符号来表示匿名参数

  ```
  
  var sum = 0
  for _ in 1...3 {
      sum += 1
  }
  ```

  

###### 7. Switch

* 在C/Objective-C语言中，case语句不会因匹配成功而中断，如果不进行手动控制，switch结构中的case子句会依次进行匹配执行。

* Swift语句优化了这一点，一个case语句匹配成功后，会自动跳出switch结构，如果不加特殊处理，switch结构中的分支只会被执行一个或者一个也不执行。 



###### 8.流程跳转

* fallthrough语句是Swift中特有的一种流程控制语句。

* Swift语言中的switch-case结构匹配到一个case后，会自动中断后面所有case的匹配操作，如果在实际开发中，需要switch-case结构不自动进行中断操作，可以使用fallthrough语句。

  ```
  var tuple = (0,0)
  switch tuple {
  case (0,0):
      print("Sure")
      fallthrough
  case(_,0):
      print("Sim")
      fallthrough
  case(0...3,0...3):
      print("SIM")
  default:
      print("")
  }
  ```

* guard-else语句也被称为守护语句，顾名思义，其作用就是确保某个条件成立才允许其后的代码执行

  ```
  func funcOne(param:Int){
      guard param > 0 else {
          return
      }
      
      print("guard")
  }
  ```

  







