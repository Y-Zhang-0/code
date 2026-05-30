# AviatorScript 5.0 零基础入门教程

## 目录

1. [什么是 AviatorScript](#什么是-aviatorscript)
2. [快速开始](#快速开始)
3. [基础语法](#基础语法)
4. [数据类型](#数据类型)
5. [运算符](#运算符)
6. [变量与赋值](#变量与赋值)
7. [条件判断](#条件判断)
8. [循环](#循环)
9. [函数](#函数)
10. [数组与集合](#数组与集合)
11. [常用函数库](#常用函数库)
12. [实战示例](#实战示例)

---

## 什么是 AviatorScript

AviatorScript 是一门运行在 Java 平台上的**轻量级脚本语言**，特点是：

- **简单易学**：语法接近自然语言，无需深厚编程基础
- **高性能**：直接编译为 Java 字节码执行
- **功能完整**：支持变量、函数、循环、条件判断等完整编程能力
- **安全可控**：可作为规则引擎、公式计算等场景使用

**适用场景**：
- 业务规则配置（如：满 100 减 20）
- 动态公式计算（如：绩效计算公式）
- 数据处理脚本（如：批量转换、过滤）

---

## 快速开始

### 安装与运行

**方式一：命令行工具**
```bash
# 下载 aviator 脚本（自动下载最新 JAR）
curl -o aviator https://raw.githubusercontent.com/killme2008/aviatorscript/master/bin/aviator
chmod +x aviator

# 运行脚本文件
./aviator hello.av
```

**方式二：Java 项目集成**
```xml
<!-- Maven 依赖 -->
<dependency>
    <groupId>com.googlecode.aviator</groupId>
    <artifactId>aviator</artifactId>
    <version>5.4.3</version>
</dependency>
```

```java
// Java 代码调用
AviatorEvaluator.execute("1 + 2 + 3");  // 返回 6
```

### 第一个脚本：Hello World

创建文件 `hello.av`：
```aviator
println("Hello, AviatorScript!");
```

运行：
```bash
./aviator hello.av
```

输出：
```
Hello, AviatorScript!
```

---

## 基础语法

### 注释

```aviator
## 这是单行注释（用两个 # 号）

## 下面是一段计算代码
let result = 1 + 2;
println(result);  ## 输出 3
```

### 语句结束符

- 每条语句用**分号 `;`** 结尾
- 函数最后一行可省略分号（作为返回值）

```aviator
let a = 10;
let b = 20;
let sum = a + b;  ## 必须加分号
```

---

## 数据类型

AviatorScript 支持以下基本类型：

### 1. 数字（Number）

```aviator
let age = 25;           ## 整数（long）
let price = 99.99;      ## 小数（double）
let big = 123456789N;   ## 大整数（bigint，后缀 N）
let precise = 3.14M;    ## 高精度小数（decimal，后缀 M）
```

### 2. 字符串（String）

```aviator
let name = "张三";              ## 双引号
let greeting = 'Hello';         ## 单引号
let message = "你好，" + name;  ## 字符串拼接
println(message);               ## 输出：你好，张三
```

**字符串插值**（更方便的拼接方式）：
```aviator
let name = "李四";
let age = 30;
p("我叫#{name}，今年#{age}岁");  ## 输出：我叫李四，今年30岁
```

### 3. 布尔值（Boolean）

```aviator
let is_adult = true;
let is_student = false;

if is_adult {
  println("已成年");
}
```

### 4. 空值（nil）

```aviator
let empty = nil;  ## 相当于 Java 的 null

if empty == nil {
  println("变量为空");
}
```

### 5. 正则表达式（Pattern）

```aviator
let phone_pattern = /\d{11}/;  ## 匹配 11 位数字

if "13812345678" =~ phone_pattern {
  println("手机号格式正确");
}
```

---

## 运算符

### 算术运算符

```aviator
let a = 10;
let b = 3;

println(a + b);   ## 加法：13
println(a - b);   ## 减法：7
println(a * b);   ## 乘法：30
println(a / b);   ## 除法：3（整数除法）
println(a % b);   ## 取余：1
```

### 比较运算符

```aviator
let x = 5;
let y = 10;

println(x == y);   ## 等于：false
println(x != y);   ## 不等于：true
println(x < y);    ## 小于：true
println(x > y);    ## 大于：false
println(x <= 5);   ## 小于等于：true
println(y >= 10);  ## 大于等于：true
```

### 逻辑运算符

```aviator
let age = 25;
let has_license = true;

## 与运算（&&）：两个条件都为真
if age >= 18 && has_license {
  println("可以开车");
}

## 或运算（||）：至少一个条件为真
if age < 18 || !has_license {
  println("不能开车");
}

## 非运算（!）：取反
println(!true);   ## false
println(!false);  ## true
```

### 三元运算符

```aviator
let age = 20;
let status = age >= 18 ? "成年" : "未成年";
println(status);  ## 输出：成年
```

---

## 变量与赋值

### 定义变量

```aviator
let name = "王五";      ## 用 let 定义变量
let age = 28;
let salary = 8000.5;
```

### 重新赋值

```aviator
let count = 0;
count = count + 1;  ## 重新赋值
println(count);     ## 输出：1
```

### 变量作用域

```aviator
let global_var = "全局变量";

fn test() {
  let local_var = "局部变量";  ## 只在函数内有效
  println(global_var);         ## 可以访问全局变量
}

test();
## println(local_var);  ## 错误！外部无法访问局部变量
```

---

## 条件判断

### if 语句

```aviator
let score = 85;

if score >= 90 {
  println("优秀");
} elsif score >= 60 {
  println("及格");
} else {
  println("不及格");
}
```

**注意**：
- 条件不需要括号 `()`
- 使用 `elsif`（不是 `else if`）
- 代码块用 `{}` 包裹

### 多条件判断

```aviator
let age = 25;
let income = 5000;

if age >= 18 && income > 3000 {
  println("符合贷款条件");
} else {
  println("不符合条件");
}
```

---

## 循环

### for 循环（遍历集合）

```aviator
## 遍历数组
let numbers = tuple(1, 2, 3, 4, 5);
for num in numbers {
  println(num);
}

## 遍历范围
for i in range(1, 6) {  ## 1 到 5（不包括 6）
  println("第#{i}次循环");
}
```

### while 循环

```aviator
let count = 0;
while count < 5 {
  println("count = #{count}");
  count = count + 1;
}
```

### 循环控制

```aviator
## break：跳出循环
for i in range(1, 10) {
  if i == 5 {
    break;  ## 遇到 5 就停止
  }
  println(i);
}

## continue：跳过本次循环
for i in range(1, 6) {
  if i == 3 {
    continue;  ## 跳过 3
  }
  println(i);  ## 输出 1, 2, 4, 5
}
```

---

## 函数

### 定义函数

```aviator
## 基本函数定义
fn greet(name) {
  return "你好，" + name;
}

println(greet("小明"));  ## 输出：你好，小明
```

### 带返回值的函数

```aviator
fn add(x, y) {
  return x + y;
}

let result = add(10, 20);
println(result);  ## 输出：30
```

### 省略 return（最后一行自动返回）

```aviator
fn multiply(x, y) {
  x * y  ## 最后一行不加分号，自动作为返回值
}

println(multiply(3, 4));  ## 输出：12
```

### 匿名函数（lambda）

```aviator
let square = lambda(x) -> x * x end;
println(square(5));  ## 输出：25

## 简写形式（5.2.4+）
let cube = fn(x) { x * x * x };
println(cube(3));  ## 输出：27
```

### 可变参数函数

```aviator
fn sum(&numbers) {
  let total = 0;
  for num in numbers {
    total = total + num;
  }
  return total;
}

println(sum(1, 2, 3));        ## 输出：6
println(sum(10, 20, 30, 40)); ## 输出：100
```

---


## 数组与集合

这是 AviatorScript 最实用的部分，掌握了集合操作，就能处理大部分数据任务。

### 数组（Tuple）

**创建数组**：
```aviator
let fruits = tuple("苹果", "香蕉", "橘子", "葡萄");

println(fruits[0]);       ## 访问第一个元素：苹果
println(count(fruits));   ## 数组长度：4

fruits[0] = "西瓜";       ## 修改元素
println(fruits[0]);       ## 输出：西瓜

## 遍历数组
for fruit in fruits {
  println("我喜欢吃" + fruit);
}
```

**创建指定类型的数组**：
```aviator
let scores = seq.array(int, 90, 85, 78, 92);  ## 整数数组
let names = seq.array(java.lang.String, "张三", "李四", "王五");  ## 字符串数组
```

**创建空数组**：
```aviator
let arr = seq.array_of(int, 5);  ## 创建长度为 5 的整数数组，默认值全是 0

for i in range(0, 5) {
  arr[i] = i * 10;  ## 赋值：0, 10, 20, 30, 40
}
```

**创建二维数组**（表格数据）：
```aviator
let table = seq.array_of(long, 3, 2);  ## 3 行 2 列

table[0][0] = 100;
table[0][1] = 200;
table[1][0] = 300;
table[1][1] = 400;
```

### 列表（List）

列表比数组更灵活，可以动态添加和删除元素。

```aviator
## 创建列表
let shopping = seq.list("牛奶", "面包", "鸡蛋");

## 访问元素
println(shopping[0]);  ## 牛奶

## 修改元素
shopping[0] = "酸奶";

## 添加元素
seq.add(shopping, "水果");

## 删除元素
seq.remove(shopping, "面包");

println(shopping);  ## [酸奶, 鸡蛋, 水果]
```

**快速创建列表**：
```aviator
## 创建 10 个 "待办" 组成的列表
let todos = repeat(10, "待办");

## 用函数生成列表（1 到 10）
let c = 0;
let numbers = repeatedly(10, lambda() -> c = c + 1; return c; end);
println(numbers);  ## [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
```

### 字典（Map）

字典用于存储"键-值"对，类似通讯录（名字 → 电话号码）。

```aviator
## 创建字典
let person = seq.map("name", "张三", "age", 25, "city", "北京");

## 读取值（两种方式）
println(person.name);           ## 张三
println(seq.get(person, "age"));  ## 25

## 修改值
person.age = 26;

## 添加新键值对
seq.add(person, "email", "zhangsan@example.com");

## 删除键值对
seq.remove(person, "city");

println(person);

## 获取所有 key 和 value
println(seq.keys(person));  ## [name, age, email]
println(seq.vals(person));  ## [张三, 26, zhangsan@example.com]
```

**从 5.2 开始，也可以用方括号访问**：
```aviator
person["name"] = "李四";
println(person["name"]);  ## 李四
```

### 集合（Set）

集合中的元素不会重复，适合去重场景。

```aviator
let tags = seq.set("Java", "Python", "Java", "Go", "Python");
println(tags);  ## [Java, Python, Go]（自动去重）

## 判断元素是否存在
println(include(tags, "Java"));    ## true
println(include(tags, "Rust"));    ## false
```

### 集合通用操作速查

| 操作 | 函数 | 示例 |
|------|------|------|
| 获取长度 | `count(coll)` | `count(list)` → 3 |
| 是否为空 | `is_empty(coll)` | `is_empty(seq.list())` → true |
| 是否包含 | `include(coll, x)` | `include(list, "a")` → true |
| 添加元素 | `seq.add(coll, x)` | `seq.add(list, "new")` |
| 删除元素 | `seq.remove(coll, x)` | `seq.remove(list, "old")` |
| 获取元素 | `seq.get(coll, key)` | `seq.get(list, 0)` |


## 集合高级操作（数据处理利器）

这些函数让你像流水线一样处理数据，非常强大。

### map — 批量转换

对每个元素执行同一操作，返回新集合：

```aviator
let prices = seq.list(100, 200, 300);

## 所有价格打 8 折
let discounted = map(prices, lambda(p) -> p * 0.8 end);
println(discounted);  ## [80.0, 160.0, 240.0]
```

### filter — 筛选过滤

只保留满足条件的元素：

```aviator
let scores = seq.list(45, 78, 92, 33, 88, 61);

## 筛选及格的成绩（>= 60）
let passed = filter(scores, lambda(s) -> s >= 60 end);
println(passed);  ## [78, 92, 88, 61]
```

### reduce — 汇总聚合

将所有元素合并为一个结果：

```aviator
let numbers = seq.list(1, 2, 3, 4, 5);

## 求和
let total = reduce(numbers, +, 0);
println("总和：" + total);  ## 总和：15

## 求乘积
let product = reduce(numbers, *, 1);
println("乘积：" + product);  ## 乘积：120
```

### sort — 排序

```aviator
let names = seq.list("Charlie", "Alice", "Bob");
println(sort(names));  ## [Alice, Bob, Charlie]

## 倒序排列
let desc = comparator(lambda(x, y) -> x > y end);
println(sort(names, desc));  ## [Charlie, Bob, Alice]
```

### 其他实用函数

```aviator
let data = seq.list(-2, -1, 0, 1, 2, 3, 0, 99, -1000, 7);

## distinct — 去重
println(distinct(data));
## [-2, -1, 0, 1, 2, 3, 99, -1000, 7]

## reverse — 逆序
println(reverse(data));
## [7, -1000, 99, 0, 3, 2, 1, 0, -1, -2]

## take_while — 收集满足条件的元素
let negatives = take_while(data, lambda(x) -> x < 0 end);
println(negatives);  ## [-2, -1, -1000]

## drop_while — 丢弃满足条件的元素
let non_neg = drop_while(data, lambda(x) -> x < 0 end);
println(non_neg);  ## [0, 1, 2, 3, 0, 99, 7]

## group_by — 分组
let grouped = group_by(data, lambda(x) -> x >= 0 end);
println(grouped);
## {false=[-2, -1, -1000], true=[0, 1, 2, 3, 0, 99, 7]}
```

### 组合使用（链式处理）

```aviator
let employees = seq.list(
  seq.map("name", "张三", "age", 28, "salary", 8000),
  seq.map("name", "李四", "age", 35, "salary", 15000),
  seq.map("name", "王五", "age", 22, "salary", 5000),
  seq.map("name", "赵六", "age", 40, "salary", 20000)
);

## 找出工资超过 10000 的员工姓名
let high_salary = map(
  filter(employees, lambda(e) -> e.salary > 10000 end),
  lambda(e) -> e.name end
);
println("高薪员工：" + high_salary);  ## 高薪员工：[李四, 赵六]

## 计算平均工资
let total = reduce(employees, lambda(sum, e) -> sum + e.salary end, 0);
let avg = total / count(employees);
println("平均工资：" + avg);  ## 平均工资：12000
```

### 集合转换

```aviator
## 数组转 Set（去重）
let arr = seq.array(int, 1, 2, 2, 3, 3, 3);
let unique = into(seq.set(), arr);
println(unique);  ## [1, 2, 3]

## 两个列表合并为字典
let keys = tuple("name", "age", "city");
let vals = seq.list("张三", 25, "北京");
let person = zipmap(keys, vals);
println(person);  ## {name=张三, age=25, city=北京}

## 连接两个集合
let a = seq.list(1, 2, 3);
let b = seq.list(4, 5, 6);
println(concat(a, b));  ## [1, 2, 3, 4, 5, 6]
```


## 闭包（进阶概念）

闭包是函数"记住"了它创建时的环境变量，即使离开了那个环境也能继续使用。

```aviator
## 创建一个计数器工厂
fn make_counter() {
  let count = 0;
  return lambda() ->
    let result = count;
    count = count + 1;
    return result;
  end;
}

let counter_a = make_counter();
let counter_b = make_counter();

println(counter_a());  ## 0
println(counter_a());  ## 1
println(counter_a());  ## 2
println(counter_b());  ## 0（独立计数）
println(counter_b());  ## 1
```

### 用闭包模拟"对象"

```aviator
fn create_rectangle(x, y) {
  let r = seq.map("x", x, "y", y);

  r.area = lambda() -> r.x * r.y end;
  r.circum = lambda() -> 2 * (r.x + r.y) end;

  return r;
}

let rect = create_rectangle(3, 4);
println("面积：" + rect.area());    ## 面积：12
println("周长：" + rect.circum());  ## 周长：14

rect.x = 10;
rect.y = 5;
println("新面积：" + rect.area());  ## 新面积：50
```


## 常用函数库

### 系统函数

| 函数 | 说明 | 示例 |
|------|------|------|
| `println(x)` / `p(x)` | 打印并换行 | `p("hello")` |
| `print(x)` | 打印不换行 | `print("hi")` |
| `type(x)` | 获取类型 | `type(1)` → `"long"` |
| `sysdate()` | 当前日期 | `sysdate()` |
| `now()` | 当前时间戳（毫秒） | `now()` |
| `rand()` | 随机数 [0, 1) | `rand()` |
| `rand(n)` | 随机整数 [0, n) | `rand(100)` |
| `long(x)` | 转为整数 | `long(3.14)` → 3 |
| `double(x)` | 转为小数 | `double(3)` → 3.0 |
| `str(x)` | 转为字符串 | `str(123)` → `"123"` |
| `range(start, end)` | 创建范围 | `range(1, 5)` → 1,2,3,4 |
| `max(a, b, ...)` | 最大值 | `max(1, 5, 3)` → 5 |
| `min(a, b, ...)` | 最小值 | `min(1, 5, 3)` → 1 |
| `assert(cond)` | 断言（false 则报错） | `assert(1 == 1)` |

### 字符串函数

| 函数 | 说明 | 示例 |
|------|------|------|
| `string.length(s)` | 字符串长度 | `string.length("hello")` → 5 |
| `string.contains(s1, s2)` | 是否包含 | `string.contains("hello", "ell")` → true |
| `string.startsWith(s1, s2)` | 是否以...开头 | `string.startsWith("hello", "he")` → true |
| `string.endsWith(s1, s2)` | 是否以...结尾 | `string.endsWith("hello", "lo")` → true |
| `string.substring(s, begin, end)` | 截取子串 | `string.substring("hello", 1, 3)` → `"el"` |
| `string.indexOf(s1, s2)` | 查找位置 | `string.indexOf("hello", "l")` → 2 |
| `string.split(s, sep)` | 分割字符串 | `string.split("a,b,c", ",")` → `["a","b","c"]` |
| `string.join(seq, sep)` | 拼接集合 | `string.join(list, ",")` → `"a,b,c"` |
| `string.replace_all(s, old, new)` | 全部替换 | `string.replace_all("aaa", "a", "b")` → `"bbb"` |

### 数学函数

| 函数 | 说明 | 示例 |
|------|------|------|
| `math.abs(x)` | 绝对值 | `math.abs(-5)` → 5 |
| `math.round(x)` | 四舍五入 | `math.round(3.6)` → 4 |
| `math.floor(x)` | 向下取整 | `math.floor(3.9)` → 3 |
| `math.ceil(x)` | 向上取整 | `math.ceil(3.1)` → 4 |
| `math.sqrt(x)` | 平方根 | `math.sqrt(9)` → 3.0 |
| `math.pow(x, y)` | x 的 y 次方 | `math.pow(2, 3)` → 8.0 |


## 与 Java 交互

### 调用 Java 静态方法

```aviator
use java.util.regex.Pattern;

let p = Pattern.compile("\d+");

if "123" =~ p {
  p("匹配成功");
}
```

### 导入 Java 方法（Java 端配置）

```java
// 批量导入静态方法
AviatorEvaluator.addStaticFunctions("str", StringUtils.class);
// 脚本中使用：str.isBlank("hello")

// 批量导入实例方法
AviatorEvaluator.addInstanceFunctions("s", String.class);
// 脚本中使用：s.indexOf("hello", "l")
```

### 自定义函数（Java 端注册）

```java
// 方式一：Java 代码实现
AviatorEvaluator.addFunction(new AddFunction());

// 方式二：lambda 定义
AviatorEvaluator.defineFunction("add", "lambda (x,y) -> x + y end");
```


## 实战示例

### 示例 1：成绩统计

```aviator
let scores = seq.list(
  seq.map("name", "张三", "score", 92),
  seq.map("name", "李四", "score", 78),
  seq.map("name", "王五", "score", 45),
  seq.map("name", "赵六", "score", 88),
  seq.map("name", "钱七", "score", 56)
);

## 及格人数
let passed = filter(scores, lambda(s) -> s.score >= 60 end);
p("及格人数：#{count(passed)}");

## 最高分
let top = reduce(scores, lambda(best, s) ->
  s.score > best.score ? s : best
end, scores[0]);
p("最高分：#{top.name}，#{top.score}分");

## 平均分
let avg = reduce(scores, lambda(sum, s) -> sum + s.score end, 0) / count(scores);
p("平均分：#{avg}");

## 按成绩分组
let groups = group_by(scores, lambda(s) ->
  if s.score >= 90 { return "优秀"; }
  elsif s.score >= 60 { return "及格"; }
  else { return "不及格"; }
end);

for entry in groups {
  let names = map(entry.value, lambda(s) -> s.name end);
  p("#{entry.key}：#{names}");
}
```

### 示例 2：购物车计算

```aviator
let cart = seq.list(
  seq.map("item", "苹果", "price", 5.5, "qty", 3),
  seq.map("item", "牛奶", "price", 12.0, "qty", 2),
  seq.map("item", "面包", "price", 8.0, "qty", 1)
);

## 计算每项小计
for item in cart {
  let subtotal = item.price * item.qty;
  p("#{item.item}: #{item.price} x #{item.qty} = #{subtotal}");
}

## 计算总价
let total = reduce(cart, lambda(sum, item) ->
  sum + item.price * item.qty
end, 0);
p("总计：#{total}元");

## 满 50 减 10
if total >= 50 {
  total = total - 10;
  p("满减优惠 -10 元，实付：#{total}元");
}
```

### 示例 3：数据清洗

```aviator
let raw_data = seq.list("  Hello  ", "", "  World ", nil, "  Aviator  ", "");

## 去空值、去空字符串、去首尾空格
let cleaned = map(
  filter(raw_data, lambda(x) ->
    x != nil && string.length(x) > 0
  end),
  lambda(x) ->
    ## 手动去除首尾空格
    let s = x;
    while string.startsWith(s, " ") {
      s = string.substring(s, 1);
    }
    while string.endsWith(s, " ") {
      s = string.substring(s, 0, string.length(s) - 1);
    }
    return s;
  end
);

## 过滤掉空字符串
let result = filter(cleaned, lambda(x) -> string.length(x) > 0 end);
p("清洗结果：#{result}");
```


## 函数重载与不定参数

### 函数重载（同名不同参数个数）

```aviator
fn describe(name) {
  "姓名：#{name}"
}

fn describe(name, age) {
  "姓名：#{name}，年龄：#{age}"
}

fn describe(name, age, city) {
  "姓名：#{name}，年龄：#{age}，城市：#{city}"
}

p(describe("张三"));              ## 姓名：张三
p(describe("张三", 25));          ## 姓名：张三，年龄：25
p(describe("张三", 25, "北京"));  ## 姓名：张三，年龄：25，城市：北京
```

### 参数解包（Unpacking）

```aviator
fn add(a, b) {
  a + b
}

let pair = seq.list(10, 20);
p(add(*pair));  ## 30（自动展开列表作为参数）
```


## 模块系统

### 导出模块

创建文件 `math_utils.av`：
```aviator
fn square(x) {
  x * x
}

fn cube(x) {
  x * x * x
}

exports.square = square;
exports.cube = cube;
```

### 导入模块

```aviator
let math = require("math_utils");

p(math.square(5));  ## 25
p(math.cube(3));    ## 27
```

- `require` 会缓存模块，多次调用不会重复编译
- `load` 每次都重新编译


## 语法速查表

| 语法 | 说明 | 示例 |
|------|------|------|
| `let x = 值` | 定义变量 | `let name = "张三"` |
| `fn name(args) { }` | 定义函数 | `fn add(x, y) { x + y }` |
| `lambda(args) -> body end` | 匿名函数 | `lambda(x) -> x * 2 end` |
| `if / elsif / else` | 条件判断 | `if x > 0 { ... }` |
| `for x in seq` | 遍历循环 | `for i in range(0, 10) { ... }` |
| `while cond { }` | 条件循环 | `while x < 10 { ... }` |
| `return x` | 函数返回 | `return result` |
| `break` | 跳出循环 | `break` |
| `continue` | 跳过本次 | `continue` |
| `##` | 注释 | `## 这是注释` |
| `"#{expr}"` | 字符串插值 | `"结果是#{1+2}"` |
| `use Class` | 导入 Java 类 | `use java.util.Date` |
| `require(path)` | 导入模块 | `require("utils")` |
| `&args` | 可变参数 | `fn test(&args) { }` |
| `*list` | 参数解包 | `add(*pair)` |


## 常见问题

**Q：为什么函数最后一行不加分号？**  
A：不加分号的表达式会自动作为返回值。加了分号，返回值变成 nil。

**Q：`elsif` 还是 `else if`？**  
A：AviatorScript 使用 `elsif`，不是 `else if`。

**Q：怎么判断变量是否存在？**  
A：使用 `is_def(x)` 函数，返回 true/false。

**Q：nil 和空字符串有什么区别？**  
A：`nil` 表示"没有值"（不存在），空字符串 `""` 表示"有值但内容为空"。

**Q：如何调试脚本？**  
A：善用 `p()` 和 `type()` 函数打印变量值和类型。

**Q：集合操作返回的是新集合还是修改原集合？**  
A：`map`、`filter`、`reduce` 等返回新集合，不修改原集合。`seq.add`、`seq.remove` 会修改原集合。

**Q：如何处理异常？**  
A：使用 `try...catch...finally` 语句（详见官方文档异常处理章节）。

**Q：正则表达式怎么用？**  
A：用 `/pattern/` 定义正则，用 `=~` 匹配，`$0`、`$1` 等获取捕获组。

---

## 学习路径建议

### 第一阶段：基础语法（1-2 天）
1. 掌握变量、数据类型、运算符
2. 学会 if/for/while 控制流
3. 能写简单的函数

### 第二阶段：集合操作（2-3 天）
1. 熟练使用数组、列表、字典
2. 掌握 map/filter/reduce 三大函数
3. 能处理实际数据（如 CSV、JSON）

### 第三阶段：进阶特性（3-5 天）
1. 理解闭包和高阶函数
2. 学会模块化组织代码
3. 与 Java 交互

### 第四阶段：实战项目
- 规则引擎：实现促销规则配置
- 数据 ETL：批量处理和转换数据
- 公式计算器：动态计算复杂公式

---

## 参考资源

- **官方 GitHub**：https://github.com/killme2008/aviatorscript
- **官方文档**：https://www.yuque.com/boyan-avfmj/aviatorscript
- **Maven 仓库**：搜索 `com.googlecode.aviator`

---

## 附录：完整函数速查

### Sequence 函数（集合处理）

| 函数 | 说明 |
|------|------|
| `count(seq)` | 获取集合长度 |
| `is_empty(seq)` | 判断是否为空 |
| `include(seq, x)` | 判断元素是否存在 |
| `map(seq, fn)` | 批量转换 |
| `filter(seq, pred)` | 筛选过滤 |
| `reduce(seq, fn, init)` | 汇总聚合 |
| `sort(seq, [cmp])` | 排序 |
| `reverse(seq)` | 逆序 |
| `distinct(seq)` | 去重 |
| `take_while(seq, pred)` | 收集满足条件的元素 |
| `drop_while(seq, pred)` | 丢弃满足条件的元素 |
| `group_by(seq, keyfn)` | 分组 |
| `zipmap(keys, vals)` | 合并为字典 |
| `concat(seq1, seq2)` | 连接集合 |
| `into(to, from)` | 集合转换 |
| `seq.every(seq, pred)` | 所有元素都满足 |
| `seq.not_any(seq, pred)` | 所有元素都不满足 |
| `seq.some(seq, pred)` | 至少一个元素满足 |
| `seq.min(seq)` | 最小值 |
| `seq.max(seq)` | 最大值 |

### 集合创建函数

| 函数 | 说明 |
|------|------|
| `tuple(x, y, ...)` | 创建数组 |
| `seq.array(type, ...)` | 创建指定类型数组 |
| `seq.array_of(type, size)` | 创建空数组 |
| `seq.list(x, y, ...)` | 创建列表 |
| `seq.set(x, y, ...)` | 创建集合（去重） |
| `seq.map(k1, v1, ...)` | 创建字典 |
| `repeat(n, x)` | 重复 n 次 x |
| `repeatedly(n, fn)` | 调用 fn n 次 |
| `range(start, end, [step])` | 创建范围 |

### 集合操作函数

| 函数 | 说明 |
|------|------|
| `seq.add(coll, x)` | 添加元素 |
| `seq.remove(coll, x)` | 删除元素 |
| `seq.get(coll, key)` | 获取元素 |
| `seq.put(coll, key, val)` | 设置元素 |
| `seq.keys(map)` | 获取所有 key |
| `seq.vals(map)` | 获取所有 value |
| `seq.contains_key(map, key)` | 判断 key 是否存在 |
| `seq.entry(key, val)` | 创建 Map.Entry |

---

**文档版本**：基于 AviatorScript 5.4.3  
**最后更新**：2026-03-31  
**适用人群**：零基础入门者、业务人员、脚本开发者

