
```sql
create table users (
	user_id bigserial primary key,
	name varchar(30) not null,
	email varchar(255) unique,
	phone varchar(20) unique,
	registration_date timestamp default now(),
	check (char_length(name) > 0),
	check (email ~* '.+@.+\..+'),
	check (phone ~ '^(\+)?((\d{2,3}) ?\d|\d)(([ -]?\d)|( ?(\d{2,3}) ?)){5,12}\d$'),
	check (registration_date <= now())
);

create table orders (
	order_id bigserial primary key,
	user_id bigint references users(user_id) on delete cascade,
	amount numeric(12, 2) not null,
	order_date timestamp default now() not null,
	status text default 'active' not null,
	constraint positive_amount CHECK (amount > 0),
	check (order_date <= now()),
	check (status in ('active', 'inactive', 'pending'))
);

insert into users (name, email, phone, registration_date) values
('Saul', 'drivesdale6@microsoft.com', '+420 399 103 2083', '2024-05-02 13:50:21'),
('Nikolia', 'nstate9@psu.edu', '+63 639 139 2267', '2024-06-09 17:55:32'),
('Martyn', 'mklezmskit@usnews.com', '+375 565 733 4965', '2024-04-23 08:11:23'),
('Darrel', 'dspilsted63@drupal.org', '+55 675 207 1744', '2024-08-02 10:32:45'),
('Dan', 'djikovsky5y@cbslocal.com', '+86 324 494 2014', '2024-04-30 12:15:43'),
('Clyve', 'cdummett67@goo.ne.jp', '+230 267 396 3055', '2024-05-14 20:21:34'),
('Cristina', 'celoi53@weibo.com', '+46 285 503 4651', '2024-06-17 09:53:21'),
('Javier', 'jguyther6a@twitter.com', '+212 846 723 9602', '2024-08-17 16:40:59'),
('Wynn', 'wcobbe1g@msn.com', '+7 166 181 2750', '2022-05-12 19:53:52'),
('Ethan', 'edingley1i@cbsnews.com', '+1 646 217 6170', '2023-09-12 10:35:12'),
('Bartholomew', 'bharsthorn1o@chron.com', '+62 209 430 1776', '2023-10-05 03:53:12');

insert into orders (user_id, amount, order_date, status) values
(1, 1099.99, '2024-05-10 20:24:56', 'active'),
(1, 525.50, '2024-05-09 09:55:15', 'inactive'),
(1, 2153.99, '2024-05-08 18:05:10', 'pending'),
(4, 999.99, '2024-08-03 06:25:24', 'pending'),
(5, 25000.00, '2024-05-15 22:05:15', 'inactive'),
(6, 638.50, '2024-05-15 15:50:34', 'active'),
(7, 2345.99, '2024-06-18 08:52:12', 'pending'),
(8, 5251.50, '2024-08-17 18:50:23', 'active'),
(2, 563.25, '2024-06-19 15:52:55', 'active'),
(2, 1950.25, '2024-06-20 09:31:56', 'active'),
(9, 5555.55, '2023-01-02 10:10:05', 'inactive'),
(10, 849.00, '2023-09-13 20:24:12', 'inactive'),
(11, 154.99, '2023-10-06 15:45:05', 'inactive');
(11, 9999.99, '2024-11-14 10:00:23', 'active');

// 1
select u.user_id, u.name, u.email, u.phone, o.order_id, o.order_date
from users u
inner join orders o on u.user_id = o.user_id
order by order_date desc;

// 2
select * from users
where user_id not in (select user_id from orders);

// 3
select user_id, count(order_id) as count_of_orders, sum(amount) as sum_of_orders from orders
group by user_id;

// 4
select u.name, u.email, u.phone, o.amount, o.order_date, o.status
from users u
inner join orders o on u.user_id = o.user_id
order by 
	case
		when o.status = 'pending' then 1
		when o.status = 'active' then 2
		when o.status = 'inactive' then 3
	end;

// 5
select user_id, name, (select sum(amount) from orders where user_id = users.user_id) as sum_of_orders
from users
where (select sum(amount) from orders where user_id = users.user_id) > 1000;

// 6
select u.user_id, u.name, u.email, u.phone, o.order_id, o.status 
from users u 
inner join orders o on u.user_id = o.user_id 
where o.status = 'inactive';

// 7
select u.user_id, u.name, min(o.amount) as min_order_amount
from users u
join orders o on u.user_id = o.user_id
group by u.user_id, u.name
having min(o.amount) > 500;

// 8
select u.name, u.email, u.phone, u.registration_date, o.order_date
from users u
inner join orders o on u.user_id = o.user_id
where extract(month from age(order_date, registration_date)) = 0 and 
	  extract(year from age(order_date, registration_date)) = 0;

// 9
select name, email, phone, registration_date
from users u
where registration_date < now() - interval '1 year'
and not exists (select 1 from orders o where o.user_id = u.user_id and o.order_date >= now() - interval '6 month');


// 10
select u.name, u.email, u.phone, o.order_date
from users u
inner join orders o on u.user_id = o.user_id
where extract(year from age(now(), o.order_date)) = 0 and 
	  extract(month from age(now(), order_date)) = 0;
```