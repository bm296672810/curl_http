# curl_http

#### 介绍
基于curl库封装的一个http请求类

#### 软件架构
软件架构说明


#### 安装教程
0. 依赖以下工具:

    cmake, git, openssl(curl的依赖项)

1.  安装curl
    1. $ git clone https://gitee.com/ellan-bm/curl.git
    2. $ cd curl
    3. $ cmake -Bbuild -H. -DOPENSSL_ROOT_DIR=/usr/local/openssl/ -DOPENSSL_LIBRARIES=/usr/local/openssl/lib
    4. $ sudo cmake --build build/ --target install
    第三步我指定了openssl的根目录和库目录是因为我本地的openssl没有安装到/usr/local/lib 目录下，如果安装openssl时使用的是默认路径可以不用指定这两项


#### 使用说明


#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
