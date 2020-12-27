# -*- coding = utf-8 -*-
# @Time : 2020/12/20 22:28
# @Author : Y-Zhang hfuu 1804012003
# @File : Spider.py
# @Software : PyCharm

# 引入自定义模块 from where import filename


import re  # 正则表达式进行文字匹配
import sqlite3  # 进行SQLite数据库操作
import urllib.error  # 指定URL,获取网页数据
import urllib.request
import xlwt  # 进行excel操作
from bs4 import BeautifulSoup  # 网页解析获取数据

# 正则表达式匹配规则
findLink = re.compile(r'<a href="(.*?)">')
findImgSrc = re.compile(r'<img.*src="(.*?)"', re.S)
findTitle = re.compile(r'<span class="title">(.*)</span>')
findRating = re.compile(r'<span class="rating_num" property="v:average">(.*)</span>')
findJudge = re.compile(r'<span>(\d*)人评价</span>')
findInq = re.compile(r'<span class="inq">(.*)</span>')
findBd = re.compile(r'<p class="">(.*?)</p>', re.S)


def main():
    baseurl = "https://movie.douban.com/top250?start="
    # 1.爬取网页
    datalist = getData(baseurl)
    dbpath = ".\\豆瓣电影Top250.xls"
    dbpath1 = ".\\MovieTop250.db"
    # 3.保存数据
    saveData(datalist, dbpath)          # 保存到excel
    saveDataDB(datalist, dbpath1)       # 保存到数据库


# 爬取网页
def getData(baseurl):
    datalist = []
    for i in range(0, 10):
        url = baseurl + str(i * 25)
        html = askURL(url)
        # 2.逐一解析数据
        soup = BeautifulSoup(html, "html.parser")
        for item in soup.find_all('div', class_="item"):
            # print(item)
            data = []
            item = str(item)

            # 获取影片详情链接
            link = re.findall(findLink, item)[0]  # re库用来通过正则表达式查找指定的字符串
            data.append(link)

            imgSrc = re.findall(findImgSrc, item)[0]  # [0]找第一个
            data.append(imgSrc)

            titles = re.findall(findTitle, item)  # 可有英文名
            if (len(titles) == 2):
                ctitle = titles[0]  # 中文
                data.append(ctitle)
                otitle = titles[1].replace("/", "")  # 外国
                otitle = re.sub('\xa0', "", otitle)  # 去掉\xa0
                data.append(otitle)
            else:
                data.append(titles[0])
                data.append(' ')

            rating = re.findall(findRating, item)[0]
            data.append(rating)

            judgeNum = re.findall(findJudge, item)[0]
            data.append(judgeNum)

            inq = re.findall(findInq, item)
            if len(inq) != 0:
                inq = inq[0].replace(".", "")
                inq = re.sub('\xa0', "", inq)
                data.append(inq)
            else:
                data.append(' ')

            db = re.findall(findBd, item)[0]
            db = re.sub('\xa0', "", db)
            db = re.sub('<br(\s+)?/>(\s+)?', " ", db)  # 去掉<br/>
            db = re.sub('/', " ", db)  # 替换/
            data.append(db.strip())  # 去掉前后空格
            datalist.append(data)
    # for item in datalist:
    #     print(item)
    return datalist


# 得到一个指定url的网页内容
def askURL(url):
    head = {  # 模拟服务器头部信息，向豆瓣服务器发送消息
        "User-Agent": "Mozilla/5.0(Windows NT 10.0;Win64;x64) AppleWebKit / 537.36(KHTML, likeGecko) Chrome / 87.0.4280.88Safari / 537.36"
    }

    request = urllib.request.Request(url=url, headers=head)
    html = ""
    try:
        response = urllib.request.urlopen(request)
        html = response.read().decode("utf-8")
        # print(html)
    except urllib.error.URLError as e:
        if hasattr(e, "code"):
            print(e.code)
        if hasattr(e, "reason"):
            print(e.reason)
    return html


# 保存数据到excel
def saveData(datalist, dbpath):
    #    pass            #pass占位无实际意义方便后期加入代码、调试等
    workbook = xlwt.Workbook(encoding="utf-8")  # 创建Workbook对象
    worksheet = workbook.add_sheet('豆瓣电影Top250', cell_overwrite_ok=True)  # 创建工作表
    col = ("电影详情链接", "图片链接", "影片中文名", "影片外国名", "评分", "评价数", "概况", "相关信息")

    for i in range(0, 8):
        worksheet.write(0, i, col[i])  # 列名(行，列，内容)
    for i in range(0, 250):
        # print("第%d条" %(i+1)
        data = datalist[i]
        for j in range(0, 8):
            worksheet.write(i + 1, j, data[j])
    workbook.save(dbpath)
    print("数据已存储到:" + dbpath)


# 保存数据到数据库
def saveDataDB(datalist, dbpath):
    init_db(dbpath)
    coon = sqlite3.connect(dbpath)
    cursor = coon.cursor()

    for data in datalist:
        for index in range(len(data)):
            if index == 4 or index == 5:
                continue
            data[index] = '"' + data[index] + '"'
        sql = '''
            INSERT INTO movieTop250 (
                info_link, pic_link, cname, ename, 
                score, rated, instroduction, info
            ) 
            VALUES (%s)''' % ",".join(data)

        cursor.execute(sql)
        coon.commit()
    print("数据已存储到:" + dbpath)
    cursor.close()
    coon.close()


# 初始化创建数据库
def init_db(dbpath):
    sql = '''
        create table movieTop250(
            id integer primary key autoincrement,
            info_link text,
            pic_link text,
            cname varchar,
            ename varchar,
            score numeric,
            rated numeric,
            instroduction text,
            info text
        )
    '''
    conn = sqlite3.connect(dbpath)  # 建立连接
    cursor = conn.cursor()  # 创建游标
    cursor.execute(sql)  # 执行sql语句
    conn.commit()  # 提交sql操作
    cursor.close()  # 关闭游标
    conn.close()  # 关闭数据库


if __name__ == "__main__":  # 当程序执行时(程序入口类似int main(){})
    # 调用函数
    main()
    print("爬取完毕")
