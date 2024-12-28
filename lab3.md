
```sql

create table Clients1 (
id_client bigserial primary key,
name varchar(100) not null,
email varchar(255) unique, 
age smallint not null, 
city varchar(100) not null, 
registration_date timestamp default now(), 
check (email ~ '.+@.+\..+'), 
constraint age_limit check (age between 18 and 100)
);


create table Clients2 (
id_client bigserial primary key,
name varchar(100) not null,
phone varchar(20) unique,
age smallint not null, 
city varchar(100) not null,
last_visit_date timestamp default now(), 
constraint age_limit check (age between 18 and 100)
);

create index idx_clients1_city on Clients1 (city);
create index idx_clients1_age on Clients1 (age);

create index idx_clients2_city on Clients2 (city);
create index idx_clients2_age on Clients2 (age);

insert into Clients1 (name, email, age, city, registration_date) values
('Bob Johnson', 'bob.johnson1@company.com', 40, 'Phoenix', '2024-01-19 10:00:00'), ('Bob Johnson', 'bob.johnson2@domain.org', 50, 'New York', '2024-06-20 08:30:10'), ('Emma Brown', 'emma.brown@live.com', 29, 'Dallas', '2024-05-15 19:40:30'), 
('Sophia Taylor', 'sophia.taylor@icloud.com', 45, 'Austin', '2024-03-05 20:15:50'),
('Alice Smith', 'alice.smith2@yahoo.com', 35, 'Houston', '2024-02-22 11:03:55'),
('John Doe', 'john.doe1@gmail.com', 25, 'New York', '2024-10-15 14:23:45'),
('Robert Smith', 'simplexample@gmail.com', 21, 'New York', '2024-10-16 13:24:31'),
('Stanley Johnson', '123@gmail.com', 20, 'Seattle', '2024-10-17 10:00:00'),
('Charlotte Wilson', 'wiiilnson@gmail.com', 27, 'Atlanta', '2023-11-10 17:00:00'),
('Michelle Ray', 'mray@gmail.com', 35, 'Boston', '2023-05-06 05:04:15');

insert into Clients2 (name, phone, age, city, last_visit_date) values
('Michael Clark', '+1-555-101-2020', 29, 'Seattle', '2024-12-03 11:00:00'), ('Jessica Adams', '+1-555-202-3030', 32, 'Miami', '2024-07-28 15:30:00'), 
('David Walker', '+1-555-303-4040', 40, 'Boston',. '2024-02-24 09:45:00'), 
('Emily Martinez', '+1-555-404-5050', 23, 'Denver', '2024-06-20 14:15:00'), ('James Lewis', '+1-555-505-6060', 36, 'San Francisco', '2024-11-15 10:30:00'), ('Charlotte Wilson', '+1-555-606-7070', 27, 'Atlanta', '2024-11-10 17:00:00'),
('Olivia Hill', '+1-555-444-5552', 41, 'New York', '2024-10-01 22:00:00'),
('Olivia Hill', '+1-555-444-5555', 31, 'Indianapolis', '2024-10-01 22:00:00'),
('Robert Smith', '+1-555-444-5553', 21, 'New York', '2024-10-17 10:35:10'),
('Stanley Johnson', '+1-555-444-5550', 20, 'Miami', '2024-10-18 11:30:41'),
('Michelle Ray', '+1-423-534-5324', 35, 'Boston', '2024-10-16 15:42:34');


// 1 Объедините данные о клиентах из двух таблиц в один список, включив
столбцы идентификатор, name, email/phone, age, city,
registration_date/last_visit_date, так чтобы названия столбцов не повторялись.

select id_client, name, email as "email/phone", age, city from Clients1 union select id_client, name, phone, age, city from Clients2

// 2 Выведите уникальные записи клиентов по комбинации "имя + город" из обеих
таблиц, исключая дубликаты с одинаковыми именем и городом.

select name, city from Clients1 union select name, city from Clients2;

// 3  Найдите клиентов, присутствующих в первой таблице, но отсутствующих во
второй, и отсортируйте результат по возрасту клиента в порядке убывания.

select name, age, city from Clients1 except select name, age, city from Clients2 order by age desc;

// 4 Отобразите клиентов из обеих таблиц, сгруппировав их по городу и
подсчитав общее количество клиентов в каждом городе, разделив их по
возрастным группам: младше 20, от 20 до 30, и старше 30.

select city, case 
	when age < 20 then 'less than 20' 
	when age between 20 and 30 then 'from 20 to 30' 
	else 'greater than 30' 
end as age_group, 
count(*) as clients 
from (select city, age from Clients1 union all select city, age from Clients2)
group by city, age_group 
order by age_group;

// 5 Выведите информацию о клиентах, у которых возраст меньше 25 в первой
таблице и больше 35 во второй.

select name, email as "email/phone", age, city from 
(select name, email, age, city from Clients1 where age < 25 union all select name, phone, age, city from Clients2 where age > 35);

// 6 Найдите клиентов с совпадающим именем, но разными городами в обеих
таблицах, и выведите их данные, включая даты регистрации и последнего
визита.

select Clients1.name as name, Clients1.email as email, Clients2.phone as phone, Clients1.city as city_1, Clients2.city as city_2, Clients1.registration_date as registration_date, Clients2.last_visit_date as last_visit_date from Clients1 join Clients2 on Clients1.name = Clients2.name and Clients1.city <> Clients2.city;

// 7 7. Выведите клиентов из обеих таблиц, у которых возраст больше 30 и
регистрация произошла более года назад, а последний визит был не позже
шести месяцев назад.

select name, age, city, registration_date, null as last_visit_date from Clients1 where age > 30 and registration_date < now() - interval '1 year' union all select name, age, city, null as registration_date, last_visit_date from Clients2 where age > 30 and last_visit_date > now() - interval '6 months';

// 8 Найдите уникальных клиентов по полному совпадению имени, возраста и
города из обеих таблиц и отсортируйте их по дате регистрации или последнего
визита в порядке возрастания.
 
select distinct name, age, city, coalesce(registration_date, last_visit_date) as date from (select name, age, city, registration_date, null as last_visit_date from Clients1 union all select name, age, city, null as registration_date, last_visit_date from Clients2) order by date asc;

// 9 Определите клиентов из первой таблицы, у которых есть однофамильцы во
второй таблице с возрастом более чем на 10 лет меньше или больше.

select Clients1.name as name, Clients1.age, Clients2.age, Clients1.city, Clients2.city from Clients1 join Clients2 on Clients1.name = Clients2.name where abs(Clients1.age - Clients2.age) > 10;

// 10 Выведите всех клиентов, у которых последний визит был в течение
последнего месяца, с указанием таблицы, в которой находится запись.

select name, age, city, registration_date as date, 'Clients1' as table_name from Clients1 where registration_date > now() - interval '1 months' union all select name, age, city, last_visit_date as date, 'Clients2' as table_name from Clients2 where last_visit_date > now() - interval '1 months';


```