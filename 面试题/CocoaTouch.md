###### 1.UITableViewCell的复用原理是怎么样的

reuseIdentifier顾名思义是一个复用标识符，是一个自定义的独一无二的字符串，用来唯一地标记某种重复样式的UITableViewCell。系统是通过reuseIdentifier来复用已经创建了的指定样式的cell，iOS中表格的cell通过复用机制来提高加载效率，因为多数情况下表格中的cell样式都是重复的，只是数据模型不同而已。因此，系统可以在保证创建一定数量的cell的 前提下（覆盖整个tableView），通过保存并重复使用已经创建的cell来提高加载效率和优化内存，避免不停地创建和销毁cell元素。

通过调用当前tableView的dequeueReusableCellWithIdentifier方法判断指定的reuseIdentifier是否有可以重复使用的cell。如果有，那么会返回可复用的cell，cell就绪之后便可以开始更新cell的数据；如果没有可以复用的cell，那么返回nil，然后会进入后面的if语句，此时创建新的cell并给它标记一个标识符reuseIdentifier。

要创建足够数量的可覆盖整个tableView的cell之后才会开始复用之前的cell（UITableView中有一个visiableCells数组保存当前屏幕可见的cell，还有一个reusableTableCells数组用来保存那些可复用的cell）。



###### 2.能否在一个视图控制器中嵌入两个tableView控制器

可以，相当于视图和视图控制器的嵌套，视图可以添加子视图，视图控制器也可以添加子控制器。



###### 3.一个tableView是否可以关联两个不同的datasource数据源

多个数据源是完全可以的，问题的重点是如何关联，因为将数据源（Model）和tableView视图的对接工作是程序员完成的，所以数据源的多少没有根本影响。处理上可以分开依次对接，也可以通过数据的集合操作先将数据整理合并成一个数据源，然后对接。



###### 4.如何对UITableView的滚动加载进行优化，防止卡顿

* 减少cellForRowAtIndexPath代理中的计算量（cell的内容计算）。
  * 先要提前计算每个cell中需要的一些基本数据，代理调用的时候直接取出。
  * 图片要异步加载，加载完成后再根据cell内部UIImageView的引用设置图片。
  * 图片数量多时，图片的尺寸要根据需要提前经过transform矩阵变换压缩好（直接设置图片的contentMode让其自行压缩仍然会影响滚动效率），必要的时候要准备好预览图和高清图，需要时再加载高清图。
  * 图片的“懒加载”方法，即延迟加载，当滚动速度很快时避免频繁请求服务器数据。
  *  尽量手动Drawing视图提升流畅性，而不是直接子类化UITableViewCell，然后覆盖drawRect方法，因为cell中不是只有一个contentview。绘制cell不建议使用UIView，建议使用CALayer。
* 减少heightForRowAtIndexPath代理中的计算量（cell的高度计算）。
  * 由于每次tableView进行update（更新）都会对每一个cell调用heightForRowAtIndexPath代理取得最新的height，会大大增加计算时间。如果表格的所有cell高度都是固定的，那么去掉heightForRowAtIndexPath代理，直接设置tableView的rowHeight属性为固定的高度。
  * 如果高度不固定，那么应尽量将cell的高度数据计算好并储存起来，代理调用的时候直接取，即将height的计算时间复杂度降低到O(1)。



###### 5.viewDidLoad和viewDidAppear的区别是什么

当界面第一次从xib文件或者storyboard加载界面，或者手写代码创建窗口从loadView加载界面时，才会调用viewDidLoad回调方法，而viewDidAppear方法在每次界面出现时都会调用，包括第一次加载，或者跳转离开后又跳转回来时。



######  6.frame和bounds有什么区别

frame是在父视图坐标系中view自身的位置和尺寸。（参照点是父亲的坐标系统）

bounds是在自身坐标系中view自身的位置和尺寸。（参照点是本身坐标系统）



###### 7. masksToBounds属性是什么？它有什么作用

masksToBounds指在设置子layer在超出父layer时是否被裁剪，YES表示裁剪，NO表示不裁剪，默认是NO；通常在通过设置layer.cornerRadius属性实现圆角效果时要设置masksToBounds为YES，以保证圆角效果的实现，但这种方法是一种很低效的实现方式，也是最简单直接的。

masksToBounds和clipsToBounds是不同的，前者指子layer层在超出父layer时是否被裁剪（masksToBounds是CALayer的属性），而后者指子view在超出父view时是否被裁剪（clipsToBounds是UIView的属性）。



###### 8. tintColor 的作用是什么

tintColor是iOS 7以后在UIView类中新增的一个属性。tintColot具有传递性，一般用来改变应用的主色调，默认为nil，表示用父视图默认的颜色进行着色。



###### 9. View和View之间的传值方式有哪些

1. 通过视图类对象的public属性变量直接传值：可以在VCSource的头文件中定义 public属性变量，这样在 VCTarget中只要有VCSource的引用，即可直接访问其中的public属性变量值。
2. 公有方法或代理方法的参数传值：在VCSource中调用VCTarget的公有方法并传入参数，即实现了在VCTarget中访问VCSource中的参数值；在VCTarget中实现VCSource的带参数代理方法即可获取VCSource中的值。
3. NSUserDefault简单数据存储全局共享传值：即在VCSource中存值，然后在 VCTarget中将值取出进行访问使用。
4. 利用通知中心NSNotificationCenter：即让VCSource向通知中心发出通知并传入参数值，同时VCTarget监听该通知从而访问VCSource传来的参数值。
5. block块传值：利用block块在视图间传值的主要应用是定义接口和回调。例如，在VCSource中定义带有block回调的对外接口方法，并将回调参数值传入block中，这样在VCTarget中调用VCSource中的该接口方法时即可在block回调中取得VCSource传来的参 数值。
6. extern全局变量传值：即在VCSource中定义extern全局变量暴露给外部访问。



###### 10.xib和storyboard相比各自的优缺点是什么

xib优点：对UI界面的设计提供了可视化界面的功能，可以通过拖动的方式来绘制简单的UI界面，大大减少了编写UI控件的代码。

xib缺点：当界面改动较大时，需要重新添加约束；当界面复杂度较高时，xib很难实现满足需求的布局；不利于团队开发，容易造成文件冲突。

storyboard优点：能够通过可视化界面将Controller的跳转关系联系起来，还能够在Controller中进行可视化布局，大大减少了开发的代码量。

storyboard缺点：当页面很多时，会显得布局混乱，无法准确判断各个视图之间的关系；不利于团队开发，容易造成冲突。



###### 11. iOS的适配

iOS的适配主要考虑两方面，一方面是功能上要适配兼容；另一方面是界面要适应不同分辨率的屏幕。

要实现功能的适配通常需要判断当前iOS系统的版本，而实现界面的适配通常需要判断当前设备的型号（屏幕分辨率）。判断iOS系统版本的方法为取UIDevice 的systemVersion系统版本值来比对。

判断机型简单的是利用屏幕分辨率（屏幕高度）的差异性，通过屏幕高度来区分iPhone7、iPhone6或者iPhone5等。



###### 12.  imageNamed和imageWithContentsOfFile有什么区别

使用imageNamed方法会自动缓存新加载的图片并会重复利用缓存的图片，

而imageWithContentsOfFile方法直接根据路径加载图片没有缓存和取缓存的过程。

imageNamed先根据指定的图片资源名称在系统缓冲中搜索图片资源，找到即返回资源，找不到然后才到硬盘等地方重新加载图片资源并缓存。imageWithContentsOfFile和imageWithData类似，不会缓存图片，将图片转化成数据对象进行加载。

关于两者的选择主要考虑它们是否缓存的特点，对于那些尺寸较小且反复使用的图片资源一般会选择imageNamed方法，利用缓存加快加载速度。同时缓存太多又会占用太多空间，因此对于那些尺寸很大且不常用甚至只用一次的图片，应该选择使用imageWithContentsOfFile方法加载，不进行缓存。

注意imageWithContentsOfFile方法不可以直接加载Assets.xcassets图集里的图片，而需要将图片拖入工程目录。



###### 13.iOS中是如何使用自定义字体的

导入自定义字体过程很简单：添加资源包到工程→在info.plist文件中注册字体→在工程Bundle Resource中复制字体资源包→代码检测查询加入的字体并使用。

