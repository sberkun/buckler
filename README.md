# Lingua Franca on Berkeley Buckler / NRF

Original Buckler Repository: https://github.com/lab11/buckler
Lingua Franca compiler: https://github.com/lf-lang/lingua-franca
Original Lingua Franca C runtime: https://github.com/lf-lang/reactor-c


# Instructions

 - Install the nightly lingua franca compiler (specifically, the `lfc` command line tool) from https://github.com/lf-lang/lingua-franca/releases. There are currently issues with this step on MacOS that will hopefully be resolved soon.

 - Install the GNU Arm Embedded Toolchain ([here](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)) and Segger J-Link ([here](https://www.segger.com/downloads/jlink/)), which are needed to flash code onto the NRF.

 - Put your source `.lf` file(s) in the `src` folder. Currently, the folder contains example test cases that you can run, but you can delete them if you don't want them.

 - Run `script-bin/lfc_build_nrf.sh src/filename.lf`, where `filename.lf` is the name of your `.lf` file. If compilation is successful, this will ask you if you want to `make flash`; if you have a board plugged in, enter `y`, otherwise, enter `n`. 
 
 - Optionally, you can add the `script-bin` folder to your path to make the previous step easier.

 - If successful, the generated C files should appear in an `src-gen/filename/` folder. You can `cd` into that folder and run `make flash` manually if you need to.

