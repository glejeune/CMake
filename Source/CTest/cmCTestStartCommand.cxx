/*=========================================================================

  Program:   CMake - Cross-Platform Makefile Generator
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
  See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "cmCTestStartCommand.h"

#include "cmCTest.h"

bool cmCTestStartCommand::InitialPass(
  std::vector<std::string> const& args)
{
  if (args.size() < 1)
    {
    this->SetError("called with incorrect number of arguments");
    return false;
    }

  const char* smodel = args[0].c_str();
  const char* src_dir = 0;
  const char* bld_dir = 0;

  if ( args.size() >= 2 )
    {
    src_dir = args[1].c_str();
    if ( args.size() == 3 )
      {
      bld_dir = args[2].c_str();
      }
    }
  if ( args.size() > 3 )
    {
    this->SetError("called with incorrect number of arguments");
    return false;
    }
  if ( !src_dir )
    {
    src_dir = m_Makefile->GetDefinition("CTEST_SOURCE_DIRECTORY");
    }
  if ( !bld_dir)
    {
    bld_dir = m_Makefile->GetDefinition("CTEST_BINARY_DIRECTORY");
    }
  if ( !src_dir )
    {
    this->SetError("source directory not specified. Specify source directory as an argument or set CTEST_SOURCE_DIRECTORY");
    return false;
    }
  if ( !bld_dir)
    {
    this->SetError("binary directory not specified. Specify binary directory as an argument or set CTEST_BINARY_DIRECTORY");
    return false;
    }
  std::cout << "Run dashboard with model " << smodel 
    << " for src dir: " << src_dir << " and binary dir: " << bld_dir << std::endl;

  int model = m_CTest->GetTestModelFromString(smodel);
  m_CTest->SetTestModel(model);
  m_CTest->SetProduceXML(true);
  if ( !m_CTest->Initialize(bld_dir) )
    {
    return false;
    }
  return true;
}


