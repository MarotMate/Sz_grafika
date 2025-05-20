# Interaktív Szobor Kiállítás

A program egy virtuális 3D szoborkiállítást jelenít meg, amelyben a felhasználó szabadon bejárhatja a teret, szobrokat nézhet meg, világítást állíthat, valamint animációkat is figyelhet meg.

kamerakezelés, modellek betöltése fájlból, textúrázás, fénykezelés, interaktivitás, animáció, használati útmutató, jól strukturált kód, Makefile használata, és figyelmeztetésmentes fordítás.

## Funkciók

- **Kamerakezelés**: A tér bejárható a `W`, `A`, `S`, `D` billentyűkkel, az egérrel pedig körbe lehet nézni.
- **Objektumok (modellek)**: A szobrok `.obj` fájlformátumból kerülnek betöltésre.
- **Animáció és mozgatás**:
  - A szobrok lassan forognak (animáció).
  - A fényforrás pozíciója mozgatható billentyűzettel.
- **Textúrák**: A szobrok, falak és padló textúrázottak (JPEG/PNG formátum).
- **Fények állítása**: A világítás intenzitása a `+` és `-` billentyűkkel szabályozható.
- **Használati útmutató**: Az `F1` gomb megnyomására egy átlátszó overlay jelenik meg a vezérlési információkkal.
- **Moduláris felépítés**: A forráskód több fájlra van bontva, jól dokumentált interfészekkel, minimális globális változóval.
- **Warning-mentes fordítás**: A program `-Wall -Wextra` opciókkal figyelmeztetés nélkül fordul.



