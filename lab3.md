
```sql

create table Clients1 (
id_client bigserial primary key,
name varchar(30) not null,
email varchar(255) unique, 
age smallint not null, 
city varchar(100) not null, 
registration_date timestamp default now(), 
check (email ~ '.+@.+\..+'), 
constraint age_limit check (age between 18 and 100)
);


create table Clients2 (
id_client bigserial primary key,
name varchar(30) not null,
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
('Bob Johnson', 'bob.johnson1@company.com', 40, 'Phoenix', '2023-07-19 10:00:00'), ('Bob Johnson', 'bob.johnson2@domain.org', 50, 'New York', '2023-06-20 08:30:10'), ('Emma Brown', 'emma.brown@live.com', 29, 'Dallas', '2023-05-15 19:40:30'), 
('Sophia Taylor', 'sophia.taylor@icloud.com', 45, 'Austin', '2023-03-05 20:15:50'),
('Alice Smith', 'alice.smith2@yahoo.com', 35, 'Houston', '2023-08-22 11:03:55'),
('John Doe', 'john.doe1@gmail.com', 25, 'New York', '2023-10-15 14:23:45');

insert into Clients2 (name, phone, age, city, last_visit_date) values
('Michael Clark', '+1-555-101-2020', 29, 'Seattle', '2023-12-03 11:00:00'), ('Jessica Adams', '+1-555-202-3030', 32, 'Miami', '2023-11-28 15:30:00'), 
('David Walker', '+1-555-303-4040', 40, 'Boston', '2023-11-24 09:45:00'), 
('Emily Martinez', '+1-555-404-5050', 23, 'Denver', '2023-11-20 14:15:00'), ('James Lewis', '+1-555-505-6060', 36, 'San Francisco', '2023-11-15 10:30:00'), ('Charlotte Wilson', '+1-555-606-7070', 27, 'Atlanta', '2023-11-10 17:00:00'),
('Olivia Hill', '+1-555-444-5552', 41, 'New York', '2023-10-01 22:00:00'),
('Olivia Hill', '+1-555-444-5555', 31, 'Indianapolis', '2023-10-01 22:00:00');

```