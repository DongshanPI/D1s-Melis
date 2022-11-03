[中文](README_CN.md) | [English](README.md)

> 东山PI-D1s运行全志 Melis RTOS 系统

![DongshanPI-D1sRunMelis-001](https://cdn.staticaly.com/gh/DongshanPI/Docs-Photos@master/DongshanPI-D1sRunMelis-001.jpg)


## 如何构建

### 开发主机环境配置		

* ubuntu-22系统主机配置： 安装获取虚拟机请参考 https://dongshanpi.com/DongshanNezhaSTU/06-ConfigHostEnv/

  启动虚拟后 安装如下软件包：

```bash
sudo apt installautoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev

sudo dpkg --add-architecture i386
sudo apt-get update

sudo apt-getinstall libc6:i386 libncurses5:i386 libstdc++6:i386 -y

sudo apt install lib32z1 -y
```



### 获取工程源码

* 码云(Gitee)
  在上一步骤安装好的ubuntu系统内打开一个新的终端，执行如下命令获取工程源码。

```ba
git clone  https://gitee.com/weidongshan/D1s-Melis
cd D1s-Melis 
git submodule update --init --recursive
```



### 编译源码

第一步需要进入到上一步获取的工程源码目录内，执行如下命令去设置编译环境

```shell
source melis-env.sh
```

第二步：同级目录下 执行lunch 命令，输入序号 4  选择  d1s-nezha 开发板配置项。

```shell
lunch
book@100ask:~/D1s-Melis$ lunch
Lunch menu... pick a combo:
The supported board:
    1. d1-h-evb-board
    2. d1s-evb-board
    3. d1s-mq
    4. d1s-nezha
What is your choice? 4

```

第三步，输入make编译整个工程。
```shell
make -j65535
```

第四步，将编译生产的各部分分区，打包成一个完整镜像
```shell
pack          # pack spi nor flash
```

最后生成的镜像在当前工程 out/d1s-nezha/ 目录下

```bash 
book@100ask:~/D1s-Melis$ ls out/d1s-nezha/
image/                           melis_8Mnor.fex                  melis_d1s-nezha_uart0_8Mnor.img
```

## 烧录镜像到开发板

使用全志官方 `PhoenixSuit` 烧写烧写上一步编译打包好的镜像文件   melis_d1s-nezha_uart0_8Mnor.img  

烧写工具使用参考: https://dongshanpi.com/DongshanNezhaSTU/03-QuickStart/#spi-nand




## 更多命令
```
== before all ==
- lunch:        lunch <product_name>-<build_variant>

== build project ==
- Cleaning targets:
-   clean	  - Remove most generated files but keep the config and
-                     enough build support to build external modules
-   mrproper	  - Remove all generated files + config + various backup files
-   distclean	  - mrproper + remove editor backup and patch files
-
- Configuration targets:
-   make menuconfig to to do the customilize configuration.
-
- Other generic targets:
-   all	  - Build all targets marked with [*]
- * melis	  - Build the bare kernel
- * modules	  - Build all modules
-   gtags        - Generate GNU GLOBAL index
-
- Static analysers:
-   checkstack      - Generate a list of stack hogs
-   namespacecheck  - Name space analysis on compiled kernel
-   versioncheck    - Sanity check on version.h usage
-   includecheck    - Check for duplicate included header files
-   export_report   - List the usages of all exported symbols
-   headers_check   - Sanity check on exported headers
-   headerdep       - Detect inclusion cycles in headers
-   coccicheck      - Check with Coccinelle
-
- Kernel selftest:
-                     running kselftest on it
-   kselftest-clean - Remove all generated kselftest files
-   kselftest-merge - Merge all the config dependencies of kselftest to existing

- jump directory:
- croot:    Jump to the top of the tree.
- cboot:    Jump to uboot.
- cboot0:   Jump to boot0.
- cdts:     Jump to device tree.
- cbin:     Jump to uboot/boot0 bin directory.
- ckernel:  Jump to kernel.
- cdevice:  Jump to target.
- ccommon:  Jump to platform common.
- cconfigs: Jump to configs of target.
- cout:     Jump to out directory of target.
- ctarget:  Jump to target of compile directory.
- crootfs:  Jump to rootfs of compile directory.
- ctoolchain: Jump to toolchain directory.
- callwinnerpk: Jump to package allwinner directory.
- ctinatest:  Jump to tinateset directory.
- godir:    Go to the directory containing a file.

== grep file ==
- cgrep:    Greps on all local C/C++ files.
```
