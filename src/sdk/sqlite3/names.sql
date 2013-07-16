
CREATE TABLE IF NOT EXISTS person
(
   personId              INTEGER PRIMARY KEY,
   givenName             VARCHAR(128),
   surname               VARCHAR(128),
   middleName            VARCHAR(128),
   birthDay              DATE
);

INSERT INTO person (givenName, surname)             VALUES ('George',   'Washington');
INSERT INTO person (givenName, surname)             VALUES ('John',     'Adams');
INSERT INTO person (givenName, surname)             VALUES ('Thomas',   'Jefferson');
INSERT INTO person (givenName, surname)             VALUES ('James',    'Madison');
INSERT INTO person (givenName, surname)             VALUES ('James',    'Monroe');
INSERT INTO person (givenName, middleName, surname) VALUES ('John',     'Quincy', 'Adams');
INSERT INTO person (givenName, surname)             VALUES ('Andrew',   'Jackson');
INSERT INTO person (givenName, middleName, surname) VALUES ('Martin',   'Van', 'Buren');
INSERT INTO person (givenName, middleName, surname) VALUES ('William',  'Henry', 'Harrison');
INSERT INTO person (givenName, surname)             VALUES ('John',     'Tyler');
