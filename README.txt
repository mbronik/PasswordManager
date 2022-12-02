Plik: data.txt
Hasło: admin

Przy błędnej próbie odszyfrowania hasła się zaszyfrują(bez odwrotnie),
nawet po wpisaniu poprawnego hasła nie będą one czytelne.
Jest to zrobione celowo. Uzyskuje się to dzięki zastosowaniu
separatorów w formie '|', które też ulegają szyfrowaniu.
Podczas odszyfrowywania z błędnym hasłem separatory pojawiają się
w różnych innych miejscach lub w ogóle. Alternatywą do tego rozwiązania jest
np. zastosowanie stałych długości poszczególnych zmiennych lub oddzielenie
poszczególnych danych enterami.
