# Základný princíp riešenia 3. zadania z IZP ak.rok 2020/2021

Naša simulácia elektrónového mikroskopu funguje na základe rovnice o vzťahu uhlov pri prechode lúčov tenkými šošovkami v 2 rozmernom priestore, ako je vidieť na obrázku. 
![Figure](../../fig1.jpg "Lom")

Na výpočet výsledného uhlu potrebujeme iba uhol α, ktorý zviera lúč s osou mikroskopu a fokálny uhol ϒ. V projekte je možné všetky potrebné veličiny dopočítať pomocou goniometrických funkcií a vlastností trojuholníkov, ak poznáme počiatočný bod lúču, jeho uhol a vlastnosti šošoviek.

Toto riešenie prevedieme do 3 rozmerného priestoru tak, že najprv vypočítame priesečník Ox a výsledný uhol β pri pohľade rovnobežnom s osou Y, potom s osou X (osa Z určuje smer, ktorým idú lúče- v obrázku z ľava doprava), akoby sme počítali rovnice pre dva rozdielne lúče. Navzájom sa ovplyvňujú iba pri vychýlení šošovky po druhej ose, kedy lúč môže zasiahnuť šošovku pred alebo za šošovkou v závislosti od vychýlenia a uhlu paprsku.

Súradnice priesečníku a uhly β sú potom dané ako počiatočné súradnice a uhly ďalšieho lúču. Tieto údaje potom môžu byť bez zmeny využité na vypočítanie prieniku paprsku s ďalšou šošovkou, alebo miesto dopadu na iné objekty mikroskopu. Vďaka tomu vieme vypočítať priebeh lúča neobmedzeným množstvom šošoviek a zaznamenávať celú jeho trasu.

Zdroj: https://www.sciencedirect.com/science/article/pii/S0030402615000364
