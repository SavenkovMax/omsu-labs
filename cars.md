## Сущности

- Клиентская база
- Сделки
- Трейд-ин сделки
- Поставщики
- Поставки
- Кредитование
- Менеджер
- Штат ремонтников
- Документы сотрудников
- Автомобили
- Комплектации
- Дополнительные функции
- Модели автомобиля 
- Двигатель
- ДВС
- Электродвигатели
- Гибридные двигатели
- Кузов
- Трансмиссия
### Клиентская база

- id клиента
- Фамилия
- Имя
- Отчество
- Телефон
- Серия паспорта
- Номер паспорта
### Сделки

- id сделки
- id клиента
- id менеджера
- id автомобиля
- Тип страхования
- Дата
- Сумма сделки
- Гарантия
- id кредита

### Трейд-ин сделки

- id трейд-ин сделки
- id клиента
- id сдаваемого автомобиля
- id нового автомобиля
- Оценочная стоимость сдаваемого автомобиля
- Сумма доплаты
- Дата сделки
- id сделки

### Поставщики

- id поставщика
- Название компании
- Инициалы контактного лица
- Телефон
- Адрес
- ИНН
- Реквизиты
### Поставки

- id поставки
- id поставщика
- id автомобиля
- Дата поставки
- Стоимость закупки
- Количество
### Кредитование

- id кредита
- id сделки
- Сумма кредита
- Дата начала
- Дата окончания
- Процент
- Количество выплат
### Менеджер

- id менеджера
- id пакета документов
- Фамилия
- Имя
- Отчество
- Количество заключенных сделок
### Штат ремонтников

- id ремонтника
- id пакета документов
- Фамилия
- Имя
- Отчество
### Документы сотрудников

- id пакета документов
- Скан трудового договора
- Серия паспорта
- Номер паспорта
- СНИЛС
- Скан медицинской справки
- Скан документа об образовании
### Автомобили

- id автомобиля
- id модели авто
- id комплектации
- Год выпуска
- В наличии

### Комплектация

- id комплектации
- id модели авто
- id трансмиссии
- id двигателя
- Название комплектации
- Оптовая цена комплектации
- Розничная цена комплектации
- Максимальная скорость
- Разгон до 100 км/час
- Тип привода
- Масса комплектации
- Расход топлива
- Объём топливного бака

### Дополнительные функции

- id функции
- Название функции
- Описание функции
- Цена
### Комплектация-функции

- id комплектации
- id функции

### Модель авто

- id модели
- id производителя
- Название модели
- id кузова
- Вместимость багажного отделения
- Вместимость салона
### Производитель автомобиля

- id производителя
- Название производителя
- Страна производителя
### Кузов

- id кузова
- Тип кузова (универсал, седан и др.)
- Длина
- Ширина
- Высота
- Клиренс
- Цвет
- Масса кузова
### Трансмиссия

- id трансмиссии
- Тип трансмиссии (МКПП, АКПП, РКПП, Вариатор)
- Количество передач
- Эффективность передачи мощности
- Наличие блокировки дифференциала
- Наличие функции противоскольжения
### Двигатель

- id двигателя
- Тип двигателя (бензиновый, дизельный, гибрид, электро, газ)
- Мощность
- Крутящий момент
- Тип топлива
- Название модели
- Серийный номер
- Год производства
- Производитель
- Масса двигателя
### ДВС

- id двс движка
- Объём двигателя
- Количество цилиндров
- Коэффициент сжатия
- Тип наддува
- Тип впрыска топлива
- Экологический стандарт выбросов
- Средний расход топлива
- Городской цикл
- Загородный цикл
- Объём топливного бака
- id двигателя

### Электродвигатели

- id электродвигателя
- Ёмкость батареи
- Запас хода на одном заряде
- Время зарядки
- id двигателя

### Гибридные двигатели

- id гибридного двигателя
- id ДВС
- id электродвигателя
- Тип гибрида