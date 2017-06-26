# Project：de Bruijn图上的编辑距离
Refer:[http://datamining-iip.fudan.edu.cn/ppts/algo/pj2017/index.html](http://datamining-iip.fudan.edu.cn/ppts/algo/pj2017/index.html)
## 更新记录
2017-5-28:<br>
前两个任务的测试数据<br>
评测系统<br>
2017-5-30:<br>
第三个任务的测试数据<br>
注意：修改了编辑过程的输出格式<br> 

## 背景
### 编辑距离
给出字符串 a 与 b，编辑距离 d(a,b) 指通过以下操作将 a 转化为 b 的最小操作次数，操作包括：<br>  
* 插入 若 a=uv,插入字符 x 得到 a=uxv
* 删除 若 a=uxv,删除字符 x 得到 a=uv 
* 替换 对于字符 x,y 且 x≠y, 将 a=uxy 转化为 a=uyv
### de Bruijn 图
在图论中，一个 k 阶 [de Bruijn](https://en.wikipedia.org/wiki/De_Bruijn_graph) 图是一个用来表示序列交叠的有向图。<br>  
* 图中的每个节点表示一个长度为 k 的字符串
* 若两个节点的字符序列有 k−1 的交叠即在这两个节点之间连一条有向边 
```
• 示例 一个 4 阶 de Bruijn 图 ABCD -> BCDE -> CDEF
• 因此在一个 k 阶 de Bruijn 图上，一个长度为 l 的路径可表示一个长度为 k+l−1 的字符串
```


### 任务
所有输入字符串中的字符均为大写字母，且字符集 |Σ|≤4 
### Task 1
	• 给出字符串 a 与 b
	• 求出它们的编辑距离，并输出编辑操作过程
	• 其中 
	
		• 字符集 |Σ|≤4
		• len(a)≤10000
		• len(b)≤10000
### Task 2
	• 给出一个 k 阶 de Bruijn 图，以及字符串 a
	• 求 de Bruijn 图上的一条路径，使其代表的字符串与 a 的编辑距离尽可能小，并输出编辑过程
	• 其中 
	
		• len(a)≤10000
		• k≤30
		• 字符集 |Σ|≤4
		• de Bruijn 图中节点数量 ≤ 10000
### Task 3（可选）
	• 题目大致同Task2
	• 提示：答案中编辑距离 d<0.3∗len(a)，且编辑步骤均匀分布
	• 数据范围 
	
		• len(a)≤100000
		• k≤30
		• 字符集 |Σ|≤4
		• de Bruijn 图中节点数量 ≤ 1000000

## 输入格式
### Task 1
	• 第一行：字符串a
	• 第二行：字符串b
### Task 2 & 3
	• 第一行：字符串a
	• 第二行：数字n，代表 k 阶 de Bruijn 图中的节点数量
	• 之后n行：长度统一为k的字符串

## 输出格式
### Task 1
	• 第一行：数字 d，代表你求出的编辑距离
	• 之后 d 行：将 a 转化为 b 的一个合法编辑过程，每行一个操作 
	
		• DEL x 
		
			• 删除字符串 a 的第 x 个字符，0≤x≤len(a)−1 
			• 注意：同一个字符不能被删除多次 
		• INS x c 
		
			• 在字符串 a 第 x 个字符前插入字符c，0≤x≤len(a)
			• 注意：若在同一个位置插入多个字符，按INS操作在输出文件中出现顺序依次插入 
		• SUB x c 
		
			• 将字符串 a 第 x 个字符替换为 c，0≤x≤n−1 
			• 注意：无法替换已删除的字符 
### Task 2 & 3
	• 第一行：途中路径所标示的字符串 s
	• 第二行：数字 d，代表你求出的编辑距离
	• 之后 d 行：将 a 转化为 s 的一个合法编辑过程，每行一个操作

## 样例数据
### Task 1
```
输入
  ABCDABADBDC
  BCDBBCC 
输出
  5
  DEL 0
  DEL 4
  DEL 6
  DEL 7
  SUB 9 C 
解释
  ABCDABADBDC
   ||| |  | |
   BCD B  BCC

#0 *BCDABADBDC
#1 *BCD*BADBDC
#2 *BCD*B*DBDC
#3 *BCD*B**BDC
#4 *BCD*B**BCC 
```
### Task 2 & 3
```
输入
  AACCATCG
  11
  ACG
	TCG
  CGA
  CGC
  CTG
  GAT
  GCA
  GCT
  ATG
  CAT
  CTT 
输出
  ACGCATG
  3
  DEL 0
  INS 3 G
  DEL 6 
解释
输出第一行为图中路径ACG-CGC-GCA-CAT-ATG对应的字符串

AAC CATCG
 || ||| |
 ACGCAT G

#0 *ACCATCG
#1 *AC G CATCG
#2 *AC G CATG 
```

### 输入文件下载
数据名称 数据类型 文件下载<br>		
task1	task1	点我下载<br>
task2	task2	点我下载<br>
task3	task3	点我下载<br>

## 评判与提交
### 评判标准
对于上述三个任务请想办法求出尽可能好（编辑距离尽可能小）的结果。<br>
请将输出文件提交至指定网页，并在期末时请提交源代码以及项目报告。<br>
我们会按照你得出的编辑距离大小排行以及你的期末报告，决定成绩。 <br>
[点我进入评测系统网站](http://datamining-iip.fudan.edu.cn/ppts/algo/pj2017/login.html) 
密码：fq35
### 编辑过程检查工具
需要python3 
[点我下载](http://datamining-iip.fudan.edu.cn/ppts/algo/pj2017/tools/judge.zip) 

## 联系我们
非常抱歉，今年因为毕业论文的关系现在才搞好算法课的pj。<br> 
由于据期末没多少时间了，所以比较困难的第三个任务改为选做。<br>
如果对pj还有什么疑问可以联系我: <br>
孙勤正 13307130098@fudan.edu.cn 

