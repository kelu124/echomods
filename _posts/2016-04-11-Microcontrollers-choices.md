---

layout: post

title: 2016-04-11 Microcontrollers choices

---


Choice of a uC: "le boulot des microcontrollers, ce qui me gene sur
l'espruino c'est le manque de sortie wifi - si on veut sortir des
donnees en wireless." Deux choix se profilent

-   WICED : STM32F205RG 120MHz ARM Cortex M3 MCU : 17 timers et 3 ×
    12-bit, 0.5 μs ADCs with up to 24 channels and up to 6 MSPS in
    triple interleaved mode, 8- to 14-bit parallel camera interface (48
    Mbyte/s max.)
-   Le WifiMCU : EMW3165 : M4: STM32F411CE @100MHz, DSP+FPU, 1×12-bit,
    2.4 MSPS A/D converter -- Ce qui me fait peur est un WifiMCU de base
    en LUA, a voir comment repasser sur du plus bas niveau. L'avantage
    par contre c'est qu'il est dispo chez hackspark, et coute 18€ au
    lieu des 35\\\$ du WICED =)

Remarques : Avec le M3 tu perds les instructions DSP et un FPU optionnel
(cf https://en.wikipedia.org/wiki/ARM\_Cortex-M). Par contre je ne sais
pas si c'est correctement exploite, ni si on en a vraiment besoin.

Il y a aussi le Module Particle "Photon"
http://www.lextronic.fr/P37394-module-particle-photon.html (M3 120 MHz
et wifi) ou l'Arietta
http://www.lextronic.fr/P32050-module-microcontrole-arietta-g25.html

-   Apparament module ferme

