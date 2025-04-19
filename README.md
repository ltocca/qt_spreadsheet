# Spreadsheet - QT

:it:

Progetto per Laboratorio di Programmazione - Foglio di Calcolo in QT

Programmato usando Qt 5.15 (EOL a fine maggio 2025), Clion, e con unit testing fornito da Google Test versione 1.16, reperibile ![qui](https://github.com/google/googletest/tree/6910c9d9165801d8827d628cb72eb7ea9dd538c5). 

#### *Funzioni*:
- Inserimento numero di righe e numero di colonne;
- Modifica di valori delle celle;
- Inserimento Formule (ora con color coding) e aggiornamento delle celle quando modificate.
- Reset della cella e conseguente rimozione della formula collegata se presente;
- Possibilità di dichiarare una formula non solamente come elenco di celle ma anche come intervallo;
- Unit test utilizzando Google Test Suite.

#### *Screenshot*

- Inserimento dimensione foglio di calcolo

![](docs/img/dimension_insertion.png)

- Foglio vuoto

![](docs/img/default_view.png)

- Inserimento formula

![](docs/img/formula_insertion.png)

- Formule inserite

![](docs/img/inserted_formulas.png)
