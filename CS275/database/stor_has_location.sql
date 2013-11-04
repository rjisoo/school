-- phpMyAdmin SQL Dump
-- version 2.11.9.4
-- http://www.phpmyadmin.net
--
-- Host: oniddb
-- Generation Time: Dec 21, 2012 at 05:15 PM
-- Server version: 5.1.63
-- PHP Version: 5.2.6-1+lenny16

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Database: `coreyg-db`
--

-- --------------------------------------------------------

--
-- Table structure for table `stor_has_location`
--

CREATE TABLE IF NOT EXISTS `stor_has_location` (
  `stor_id` int(11) NOT NULL,
  `state_name` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`stor_id`),
  KEY `state_name` (`state_name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `stor_has_location`
--


--
-- Constraints for dumped tables
--

--
-- Constraints for table `stor_has_location`
--
ALTER TABLE `stor_has_location`
  ADD CONSTRAINT `stor_has_location_ibfk_1` FOREIGN KEY (`state_name`) 
REFERENCES `states` (`state_name`) ON DELETE NO ACTION ON UPDATE 
CASCADE,
  ADD CONSTRAINT `stor_has_location_ibfk_2` FOREIGN KEY (`stor_id`) 
REFERENCES `storage` (`stor_id`) ON DELETE CASCADE ON UPDATE CASCADE;

