#ifndef __DATASOURCE_HPP
#define __DATASOURCE_HPP

#include <string>

enum DataSource { Gurjit=0, Gisaid };

DataSource classifyFAIorFastaFilename(const std::string& filename);
std::string describeDataSource(DataSource ds);

#endif
