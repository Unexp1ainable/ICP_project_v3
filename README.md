# ICP_project_v3
Project fo 3rd variant of VUT FIT ICP project


    Základní požadavky
        aplikace zobrazí schématický 3D model elektronového svazku, čočkových modulů, vzorku, zdroje elektronů a detektoru
        pro schématické zobrazení stačí využití jednoduchých tvarů jako krychle, válec, komolý kužel, …
        elektronový svazek musí být viditelný po celé jeho cestě, ať už díky geometrickému uspořádání, či průhledností ostatních komponent
        se schématickým modelem je možno rotovat, zmenšovat/zvětšovat ho (zoom) a pohybovat s ním ve třech osách (translace)
        elektronový svazek vzniká ve zdroji, prochází soustavou čočkových modulů, vzorkem, další soustavou čočkových modulů a v ideálním případě končí dopadem na detektor
        zdroj elektronů produkuje kolineární svazek zvolenéhp průřezu
            (Pozn: Ve schématických nákresech bývá nekolineární zdoj s čočkou, která koleneární zvazek vytváří - tento celek lze chápat jako zdroj).
        čočkový modul je parametrický a lze mu definovat optickou mohutnost a vychýlení ve dvou osách (kolmých na sebe samé a na osu zdroj -> detektor)
        střed všech čočkových modulů leží na ose zdroj -> detektor a jejich pozice je definována pouze vzdáleností od zdroje/detektoru
            (Pozn: Modul samotný je fyzicky vycentrovaný na ose, nicméně provádí transformaci elektronového svazku. První operací je "roztažení/zúžení" svazku definované optickou mohutností a druhá operace je vychýlení svazku. Ten tedy již nebude mít střed na ose, ale pomocí tohoto vychýlení lze směrovat svazek na kterékoliv místo na vzorku. Princip fungování je téměř totožný s CRT monitory, kdy zaostřený svazek cestuje po obrazovce.)
        počáteční konfigurace scény (počet, pozice a parametry jednotlivých objektů) je načítána ze souboru jehož formát si můžete určit sami
        konfiguraci scény lze uložit do souboru
        součástí UI bude informace o průchodu svazku vzorkem (pozice X a Y na povrchu vzorku, dále velikost svazku v ose X a Y v místě průchodu)
        součástí UI bude informace o dopadu svazku na detektor (pozice X a Y na povrchu detektoru, dále velikost svazku v ose X a Y v místě dopadu)
        pozice a rotace vzorku je definována relativně k ose zdroj -> detektor
    Interaktivní zásahy
        možnost přidávat a odebírat čočkové moduly
        možnost měnit pozici a parametry čočkových modulu
            pozicí se rozumí vzdálenost od zdroje/detektoru
            parametry se rozumí mohutnost a vychýlení svazku
        možnost měnit pozici a rotaci vzorku
        možnost měnit pozici (vzdálenost od zdroje) detektoru
    Inspirace
        Schématické znázornění svazku elektronového mikroskopu zahrnující zdroj, čočkové moduly, vzorek a detektor: https://www.britannica.com/technology/transmission-electron-microscope
        Video na anglické wikipedii zachytávající část řešení: https://en.wikipedia.org/wiki/Transmission_electron_microscopy
    Rozšíření pro tříčlenný tým
        Vytvořte jednoduchý „ray-tracing“ kdy jako zdroj elektronů bude načítána bitmapa v odstínech šedi určující intenzitu svazku v daných bodech. Vzorek bude také načítán jako bitmapa v odstínech šedi určující „propustnost“ pro elektronový svazek a UI zobrazí výsledný obrazec dopadající na detektor. Ukázka viz video na anglické wiki.
    Součást odevzdání
        Připravte alespoň 5 konfigurací čočkových modulů tak, aby paprsek dopadal na detektor
