--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: metrix; Type: DATABASE; Schema: -; Owner: metrixadmin
--

CREATE DATABASE metrix WITH TEMPLATE = template0 ENCODING = 'UTF8' LC_COLLATE = 'en_GB.UTF-8' LC_CTYPE = 'en_GB.UTF-8';


ALTER DATABASE metrix OWNER TO metrixadmin;

\connect metrix

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

--
-- Name: datapoint_id; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE datapoint_id
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.datapoint_id OWNER TO postgres;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: datapoints; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE datapoints (
    id integer DEFAULT nextval('datapoint_id'::regclass) NOT NULL,
    server_id integer,
    "time" timestamp without time zone,
    identifier text,
    value text,
    metric_type character varying(64)
);


ALTER TABLE public.datapoints OWNER TO postgres;

--
-- Name: server_id_sequence; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE server_id_sequence
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.server_id_sequence OWNER TO postgres;

--
-- Name: servers; Type: TABLE; Schema: public; Owner: postgres; Tablespace: 
--

CREATE TABLE servers (
    server_id integer DEFAULT nextval('server_id_sequence'::regclass) NOT NULL,
    ip_address text,
    servername text,
    nickname text
);


ALTER TABLE public.servers OWNER TO postgres;

--
-- Name: datapoints_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY datapoints
    ADD CONSTRAINT datapoints_pkey PRIMARY KEY (id);


--
-- Name: servers_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres; Tablespace: 
--

ALTER TABLE ONLY servers
    ADD CONSTRAINT servers_pkey PRIMARY KEY (server_id);


--
-- Name: datapoints_server_id_identifier_idx; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE INDEX datapoints_server_id_identifier_idx ON datapoints USING btree (server_id, identifier);


--
-- Name: servers_server_id_idx; Type: INDEX; Schema: public; Owner: postgres; Tablespace: 
--

CREATE UNIQUE INDEX servers_server_id_idx ON servers USING btree (server_id);


--
-- Name: datapoints_server_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY datapoints
    ADD CONSTRAINT datapoints_server_id_fkey FOREIGN KEY (server_id) REFERENCES servers(server_id);


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- Name: datapoint_id; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE datapoint_id FROM PUBLIC;
REVOKE ALL ON SEQUENCE datapoint_id FROM postgres;
GRANT ALL ON SEQUENCE datapoint_id TO postgres;
GRANT USAGE ON SEQUENCE datapoint_id TO metrixinsert;
GRANT ALL ON SEQUENCE datapoint_id TO metrixadmin;


--
-- Name: datapoints; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE datapoints FROM PUBLIC;
REVOKE ALL ON TABLE datapoints FROM postgres;
GRANT ALL ON TABLE datapoints TO postgres;
GRANT ALL ON TABLE datapoints TO metrixadmin;
GRANT INSERT ON TABLE datapoints TO metrixinsert;


--
-- Name: server_id_sequence; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON SEQUENCE server_id_sequence FROM PUBLIC;
REVOKE ALL ON SEQUENCE server_id_sequence FROM postgres;
GRANT ALL ON SEQUENCE server_id_sequence TO postgres;
GRANT USAGE ON SEQUENCE server_id_sequence TO metrixinsert;
GRANT ALL ON SEQUENCE server_id_sequence TO metrixadmin;


--
-- Name: servers; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE servers FROM PUBLIC;
REVOKE ALL ON TABLE servers FROM postgres;
GRANT ALL ON TABLE servers TO postgres;
GRANT ALL ON TABLE servers TO metrixadmin;
GRANT SELECT,INSERT,UPDATE ON TABLE servers TO metrixinsert;


--
-- PostgreSQL database dump complete
--

