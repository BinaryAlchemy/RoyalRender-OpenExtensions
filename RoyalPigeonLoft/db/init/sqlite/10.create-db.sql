-- begin SESSIONS
create table SESSIONS (
    ID blob primary key,
    USER varchar(255),
	PASSHASH varchar(125),
    EXPIRATION integer
);
-- end SESSIONS

-- begin CONNECTION_STATISTICS
create table CONNECTION_STATISTICS (
    ID integer primary key,
    JSON varchar(255),
    TIMESTAMP integer
);
-- end CONNECTION_STATISTICS

-- begin MEMORY_USAGE_STATS
create table MEMORY_USAGE_STATS (
    ID integer primary key,
    WORKER_ID varchar(255),
    MEMORY_OCCUPATION integer not null default 0,
    TIMESTAMP integer
);
-- end MEMORY_USAGE_STATS

-- begin USER_SETTINGS
create table USER_SETTINGS (
    NAME varchar(255) primary key,
    JOBS_BASIC integer not null default 1,
    JOBS_SCENE integer not null default 1,
    JOBS_PROGRESS integer not null default 1,
    JOBS_TIME integer not null default 1,
    JOBS_STATUS integer not null default 1,
    JOBS_DEBUG integer not null default 0,
    CLIENTS_BASIC integer not null default 1,
    CLIENTS_CPU integer not null default 1,
    CLIENTS_GPU integer not null default 1,
    CLIENTS_TEMPERATURE integer not null default 1,
    CLIENTS_DEBUG integer not null default 0,
    FILTER_PROJECT varchar(255) not null default '-- all --',
    FILTER_USER varchar(255) not null default '-- all --',
    FILTER_APP varchar(255) not null default '-- all --',
    FILTER_AGE varchar(50) not null default '-- all --',
    FILTER_NOTRENDERING integer not null default 1,
    FILTER_RENDERING integer not null default 1,
    FILTER_DISABLED integer not null default 1,
    FILTER_WAITING integer not null default 1,
    FILTER_FINISHED integer not null default 1

);
-- end USER_SETTINGS
