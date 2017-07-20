# Testing the specs of the In / out for the [analog processing board](/retired/goblin/)

## Test of the analog processing board

Data sampled at 10Msps on the [PRUDAQ](/retired/toadkiller/) on both channels.

## Code

See the Jupyter notebook [In-Out.ipynb](/retired/toadkiller/data/test_enveloppe/In-Out.ipynb)

Data is saved [here](/retired/toadkiller/data/test_enveloppe/dual_entry.bin). It's 32Mb of sampling at 10 Msps.

Part of the data is the signal going in the board, the second part is what comes out of the probe.

Remarks : 

* Raw data differs a little bit of shown data: the input signal is biaised to fit into the PRUDAQ [0,2V] range, and the SigOut data does not reach the full gain to fill the 3.3V of the output - to stay within a "safe" range for the acquisition board.
* One will note that the prudaq connectors are stray wires, and the board presents a significant noise on the SigOut channel.

### Signal in / signal out

The signal sent in is 50mVpp, the carier is at 2MHz. Linear decrease from t0 to the end.

![](/retired/toadkiller/data/test_enveloppe/SigInSigOut.png)

### Details at the enveloppe level

The period of the signal is 2 MHz. The first peak has 1 period, the second 2, height is half of the first peak, and the 3rd has 3 periods, height 1/4th of the first peak. 

![](/retired/toadkiller/data/test_enveloppe/Details.png)
