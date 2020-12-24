---

layout: post

title: 2019-10-26 Some lit3 progress

---


-   Good progress, stupid capa was in the way on ADC clock. Now
    acquisitions seem more okay:
-   [here some good
    experiment](https://github.com/kelu124/echomods/tree/master/matty/20191023a)
-   @done updates on new pHAT
-   remove this capa, remove i2c pullups for the thermometers (that was
    cost 5\$ ! :/ )
-   connecter le ice40 au i2c rpi
-   pouvoir connecter des ios sur l'uart du rpi
-   router les gpio daughter existantes plutôt sur les pins pcm du rpi
    pour un jour essayer de sortir des données en i2s (GPIO26, 20,
    21, 18)
-   du coup, mettre possiblement les Pulse controls sur des GPIOs non
    spécifiques comme GPIO05, 06, 13, 19.
-   Niveau header RPi, on peut connecter les SPI\_EXT MISO / CS du coup.
-   Use 5 first bytes of a read to store the bin number / board ID ?
-   Need to make progress on this RTL-SDR for ultrasound ;)
-   @done find the right jekyll theme to leave gitbook
-   see
    https://help.github.com/en/github/working-with-github-pages/adding-a-theme-to-your-github-pages-site-using-jekyll
-   https://pmarsceill.github.io/just-the-docs/ seem to fit the bill =)

