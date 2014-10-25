%module jsiotkit_iotkit

%include "account_management.h"
%{
    #include "account_management.h"
%}

%include "advanced_data_inquiry.h"
%{
    #include "advanced_data_inquiry.h"
%}

%include "aggregated_report_interface.h"
%{
    #include "aggregated_report_interface.h"
%}

%include "alert_management.h"
%{
    #include "alert_management.h"
%}

%include "component_catalog.h"
%{
    #include "component_catalog.h"
%}

%include "data_api.h"
%{
    #include "data_api.h"
%}

%include "device_management.h"
%{
    #include "device_management.h"
%}

%include "rule_management.h"
%{
    #include "rule_management.h"
%}

%include "iotkit.h"
%{
    #include "iotkit.h"
%}

%include "rest.h"
%{
    #include "rest.h"
%}

%include "util.h"
%{
    #include "util.h"
%}
