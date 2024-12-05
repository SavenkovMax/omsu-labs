# Wine cellar

### Wine

- id_wine (PK)
- color
- production_date
- production_country
- alcohol
- sweetness
- volume
- description

### Wine suppliers

- id_supplier (PK)
- name_supplier
- country_supplier
- contacts_supplier

### Supply accords (Договор на поставку)

- id_accord (PK)
- id_supplier (FK ,  NULLable)
- id_restraurant (FK, NULLable)
- date_signed

### Wine supply

- id_supply (PK)
- id_accord (FK)
- id_sommelier (FK)
- date_supply

### Supply details

- id_supply, id_wine (PKs)
- quantity
- purchase_price

### Restaurant

- id_restaurant (PK)
- name_restarurant
- address_restaurant
- contacts_restaurant

### Sommelier

- id_sommelier (PK)
- surname_sommelier
- name_sommelier
- patronymic_sommelier

Прим: NULLable означает опциональность значения атрибута. Логика работы поставки стала единой для поставки в погреб и в ресторан. В случае если у нас идёт поставка в ресторан, id_restaurant будет не NULL, а id_supplier будет NULL. Если поставка в погреб, то наоборот.

### Functional dependencies

1. id_wine -> {color, production_date, production_country, alcohol, sweetness, volume, description}
2. id_supplier -> {name_supplier, country_supplier, contacts_supplier}
3. id_restraurant -> {name_restaurant, address_restaurant, contacts_restaurant}
4. id_accord -> {id_supplier, id_restaurant, date_signed}
5. id_supply -> {id_accord, id_sommelier, date_supply}
6. {id_supply, id_wine} -> {quantity, purchase_price}
7. id_sommelier -> {surname_sommelier, name_sommelier, patronymic_sommelier, id_restaurant}


1. A1 -> {A2, A3, A4, A5, A6, A7, A8}
2. A9 -> {A10, A11, A12}
3. A14 -> {A21, A22, A23}
4. A13 -> {A9, A14, A15}
5. A16 -> {A13, A17, A18} 
6. {A16, A1} -> {A19, A20}
7. A17 -> {A24, A25, A26}

### Minimal cover

1. A1 -> A2
2. A1 -> A3
3. A1 -> A4
4. A1 -> A5
5. A1 -> A6
6. A1 -> A7
7. A1 -> A8
8. A9 -> A10
9. A9 -> A11
10. A9 -> A12
11. A14 -> A21
12. A14 -> A22
13. A14 -> A23
14. A13 -> A14
15. A13 -> A15
16. A13 -> A9
17. A16 -> A13
18. A16 -> A17
19. A16 -> A18
20. {A1, A16} -> A19
21. {A1, A16} -> A20
22. A17 -> A24
23. A17 -> A25
24. A17 -> A26
### Attributes set

A1 = id_wine
A2 = color
A3 = production_date
A4 = production_country
A5 = alcohol
A6 = sweetness
A7 = volume
A8 = description
A9 = id_supplier
A10 = name_supplier
A11 = country_supplier
A12 = contacts_supplier
A13 = id_accord
A14 = id_restraurant
A15 = date_signed
A16 = id_supply
A17 = id_sommelier
A18 = date_supply
A19 = quantity
A20 = purchase_price
A21 = name_restaurant
A22 = address_restaurant
A23 = contacts_restaurant
A24 = surname_sommelier
A25 = name_sommelier
A26 = patronymic_sommelier
