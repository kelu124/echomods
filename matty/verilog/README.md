# un0rick_verilog

Porting of [original un0rick repository][original_repo] FPGA VHDL code to Verilog.

TODO list:
* [x] ~~gray_counter.vhd~~
* [x] ~~asyn_fifo.vhd~~
* [x] ~~spi_data_path.vhd~~
* [x] ~~sclk_gen.vhd~~
* [x] ~~spi_master.vhd~~
* [x] ~~spi_slave_ice.vhd~~
* [x] ~~hpll_core_primitive~~
* [x] ~~pll128M2.vhd~~
* [x] ~~matty.vhd~~



Original hierarchy of the project is: 

![Original Hiearchy][original_hiearchy]

```
matty.vhd
    ->pll128M2.vhd
        ->pll_core_primitive
    ->spi_slave_ice.vhd
    ->spi_master.vhd
        ->sclk_gen.vhd
        ->spi_data_path.vhd
            ->asyn_fifo.vhd
                ->gray_counter.vhd
                ->gray_counter.vhd
```





[original_repo]: https://github.com/kelu124/un0rick/tree/master/software
[original_hiearchy]: doc/original_hiearchy.png