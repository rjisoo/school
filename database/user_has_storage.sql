-- phpMyAdmin SQL Dump
-- version 2.11.9.4
-- http://www.phpmyadmin.net
--
-- Host: oniddb
-- Generation Time: Dec 21, 2012 at 05:17 PM
-- Server version: 5.1.63
-- PHP Version: 5.2.6-1+lenny16

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Database: `coreyg-db`
--

-- --------------------------------------------------------

--
-- Table structure for table `user_has_storage`
--

CREATE TABLE IF NOT EXISTS `user_has_storage` (
  `user_share_id` int(11) NOT NULL AUTO_INCREMENT,
  `cust_id` int(11) NOT NULL,
  `stor_id` int(11) DEFAULT NULL,
  PRIMARY KEY (`user_share_id`),
  UNIQUE KEY `cust_id` (`cust_id`),
  UNIQUE KEY `stor_id` (`stor_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Dumping data for table `user_has_storage`
--


