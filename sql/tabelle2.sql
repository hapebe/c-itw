use testdatenbank;

-- show tables;
drop table if exists tabelle2;

create table tabelle2 (spalte1 varchar(30), spalte2 varchar(30));
ALTER TABLE tabelle2 CHANGE spalte1 vorname varchar(30);
ALTER TABLE tabelle2 CHANGE spalte2 nachname varchar(30);

-- show create table tabelle2;
show fields from tabelle2;

insert into tabelle2 (vorname, nachname) values ('Max', 'Mustermann');
insert into tabelle2 (vorname, nachname) values ('Erika', 'Musterfrau');
insert into tabelle2 values ('Hans-Peter', 'Bergner');

ALTER TABLE tabelle2 ADD uid int auto_increment primary key FIRST;
-- select * from tabelle2;

ALTER TABLE tabelle2 CHANGE uid uid int;
ALTER TABLE tabelle2 DROP PRIMARY KEY;
show fields from tabelle2;
select * from tabelle2;

-- ALTER TABLE tabelle2 DROP uid;
-- select * from tabelle2;

select * from tabelle2 into outfile 'D:/it5source/sql/tabelle2.out' FIELDS TERMINATED BY ';' OPTIONALLY ENCLOSED BY '"' LINES TERMINATED BY '\n';

-- delete from tabelle2;

