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
-- Table structure for table `stor_belongs_tier`
--

CREATE TABLE IF NOT EXISTS `stor_belongs_tier` (
  `stor_id` int(11) NOT NULL,
  `tier_name` varchar(255) NOT NULL,
  UNIQUE KEY `stor_id` (`stor_id`),
  KEY `tier_id` (`tier_name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `stor_belongs_tier`
--


--
-- Constraints for dumped tables
--

--
-- Constraints for table `stor_belongs_tier`
--
ALTER TABLE `stor_belongs_tier`
  ADD CONSTRAINT `stor_belongs_tier_ibfk_1` FOREIGN KEY (`stor_id`) 
REFERENCES `storage` (`stor_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `stor_belongs_tier_ibfk_2` FOREIGN KEY (`tier_name`) 
REFERENCES `tiers` (`tier_name`) ON DELETE CASCADE ON UPDATE CASCADE;

