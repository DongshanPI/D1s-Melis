[中文](README_CN.md) | [English](README.md)

> Allwinner melis RTOS for DongshanPI-D1s.

![DongshanPI-D1sRunMelis-001](https://cdn.staticaly.com/gh/DongshanPI/Docs-Photos@master/DongshanPI-D1sRunMelis-001.jpg)


## How to build

### Host Config

* ubuntu-22 install tools

```bash
sudo apt installautoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev

sudo dpkg --add-architecture i386
sudo apt-get update

sudo apt-getinstall libc6:i386 libncurses5:i386 libstdc++6:i386 -y

sudo apt install lib32z1 -y
```



### Get Code

* Github

```ba
git clone  https://github.com/DongshanPI/D1s-Melis.git
cd D1s-Melis 
git submodule update --init --recursive
```



### Build Code

Register the environment variables of the SDK with the compilation server host;

```shell
source melis-env.sh
```

Enter lunch, then enter 2, and select the d1s scheme "d1s-evb-board";
```shell
lunch
```

Build projcet
```shell
make -j65535
```

Pack the target image
```shell
pack          # pack spi nor flash
pack -a nand  # pack spi nand flash \ sd card
```



## How to download

Using the `PhoenixSuit` tool to burns the `melis_d1s-evb-board_uart0_8Mnor.img` firmware in the `out` directory.

Referencelink: https://dongshanpi.com/DongshanNezhaSTU/03-QuickStart/#spi-nand




## Command
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
