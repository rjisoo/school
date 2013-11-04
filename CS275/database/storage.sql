-- phpMyAdmin SQL Dump
-- version 2.11.9.4
-- http://www.phpmyadmin.net
--
-- Host: oniddb
-- Generation Time: Dec 21, 2012 at 05:14 PM
-- Server version: 5.1.63
-- PHP Version: 5.2.6-1+lenny16

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Database: `coreyg-db`
--

-- --------------------------------------------------------

--
-- Table structure for table `storage`
--

CREATE TABLE IF NOT EXISTS `storage` (
  `stor_id` int(11) NOT NULL AUTO_INCREMENT,
  `space_avail` int(11) NOT NULL,
  `storage_assigned` char(1) NOT NULL,
  PRIMARY KEY (`stor_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Dumping data for table `storage`
--


