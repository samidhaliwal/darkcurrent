#!/usr/local/bin/python
import math
from itertools import islice
from collections import Counter

class AnalyzeFile():
    def __init__(self, filename):
        self.filename = filename
        self.fi_name = '/Users/dhaliwal/Work/Alignment/DarkCurrent/acqidfiles_DC/'+filename+'.acq'
        self.fo_name = '/Users/dhaliwal/Work/Alignment/DarkCurrent/acqidfiles_DC/'+filename+'_TDarkCurrent.acq'
        self.acquire_ll = []
        self.instrument_ll = []
        self.end_ll = []
        self.ip_ll = []
        self.driver_ll = []
        self.mux_ll = []

    def FindRelevantLines(self):
        'Find the lines in an acquisifier file corresponding to aquire, instrument and end statements'
        'Return a set of 3 lists, with values for each image. Index of each list corresponds to same image'
        lookup_acquire = 'acquire:'
        lookup_instrument = 'instrument:'
        lookup_ip = 'daq_ip_addr'
        lookup_driver = 'daq_driver_socket'
        lookup_mux = 'daq_mux_socket'
        lookup_end = 'end.'
        lookup_exception = 'acquisifier'

        acquire_line_list = []
        instrument_line_list = []
        ip_line_list = []
        driver_line_list = []
        mux_line_list = []
        end_line_list = []

        with open(self.fi_name) as fi:
            for num, line in enumerate(fi):
                if lookup_acquire in line:
                    acquire_line_list.append(num)
                if lookup_instrument in line:
                    instrument_line_list.append(line.strip().split('{')[1][:-1])
                if lookup_end in line:
                    end_line_list.append(num)
                if lookup_ip in line:
                    ip_line_list.append(line.strip().split('{')[1][:-1]) #Only want to store the value between { and }
                if lookup_driver in line:
                    driver_line_list.append(line.strip().split('{')[1][:-1])
                if lookup_mux in line:
                    mux_line_list.append(line.strip().split('{')[1][:-1])

        self.acquire_ll = acquire_line_list
        self.instrument_ll = instrument_line_list
        self.ip_ll = ip_line_list
        self.driver_ll = driver_line_list
        self.mux_ll = mux_line_list
        self.end_ll = end_line_list

        return

    def RunCheck(self):
        'Check that incoming acquisifier scripts are interpretted the correct way'
        self.FindRelevantLines()
        instrument_count = Counter(self.instrument_ll)
        total_val = 0
        diag_val = 0
        
        for type,count in instrument_count.most_common():
            print '%s : %d' % (type, count)#instrument_count[instrument_type])
            total_val = total_val + count
            if (type == 'Diagnostic'):
                diag_val = diag_val + count
        
        check_len = len(self.acquire_ll)
        if (check_len != len(self.instrument_ll)):
            print 'Problem: Number of acquire lines not same as lines with instrument'
            print 'Number acquire: '+str(check_len)
            print 'Number instrument: '+str(len(self.instrument_ll))
            return 1
        if (check_len != len(self.end_ll)):
            print 'Problem: Number of acquire lines not same as lines with end'
            print 'Number acquire: '+str(check_len)
            print 'Number end: '+str(len(self.end_ll))
            return 1
        if (check_len != len(self.ip_ll)):
            print 'Problem: Number of acquire lines not same as lines with daq_ip_addr'
            print 'Number acquire: '+str(check_len)
            print 'Number ip: '+str(len(self.ip_ll))
            return 1
        if (check_len != len(self.driver_ll)):
            print 'Problem: Number of acquire lines not same as lines with daq_driver_socket'
            print 'Number acquire: '+str(check_len)
            print 'Number driver: '+str(len(self.driver_ll))
            return 1
        if (check_len != len(self.mux_ll) + diag_val):
            print 'Problem: Number of daq_mux_socket(s) seems incorrect'
            print 'Number acquire: '+str(check_len)
            print 'Number mux: '+str(len(self.mux_ll))
            print 'Number mux and diagnostics: '+str(len(self.mux_ll)+diag_val)
            return 1

        return 0


    def WriteOutput(self):
        'write output if all is okay'
        check = self.RunCheck()
            # if (check != 0):
            #return 1
        
        fo = open(self.fo_name, 'w')
        fi = open(self.fi_name, 'r')
        fheader = open("/Users/dhaliwal/Work/Alignment/DarkCurrent/acqidfiles_DC/header.txt", 'r')
        lines = fi.readlines()
        muxcount_adjust = 0
        
        ip_temp = ""
        driver_temp = ""
        mux_temp = ""
        
        for line in fheader:
            fo.write(line)
        
        
        for i, val in enumerate(self.acquire_ll):# in range(0, len(self.acquire_ll)):
            startval = val
            endval = self.end_ll[i]+1
            thisinstrument = self.instrument_ll[i]
            thisip = self.ip_ll[i]
            thisdriver = self.driver_ll[i]
            
            if (thisinstrument == 'Diagnostic'):
                muxcount_adjust = muxcount_adjust+1
                for line in range(startval, endval):
                    fo.write(lines[line])
                fo.write('\n')
									
            if (thisinstrument == 'Thermometer'):
		muxcount_adjust = muxcount_adjust+1
		for line in range(startval, endval):
		    fo.write(lines[line])
		fo.write('\n')
				
				
            thismux = self.mux_ll[i-muxcount_adjust]

            if (thisinstrument == 'BCAM'):
                if (thisip != ip_temp or driver_temp != thisdriver or mux_temp != thismux):
                    ip_temp = thisip
                    driver_temp = thisdriver
                    mux_temp = thismux

                    for line in range(startval, endval):
                        if "name: {" in lines[line]:
                            suffix = lines[line].rfind("_")
                            newname = lines[line][:suffix]+"}\n"
                            fo.write(newname)
                        elif "daq_source_device_element" in lines[line]:
                            fo.write("	daq_source_device_element {7}\n")
                        elif "daq_flash_seconds" in lines[line]:
                            fo.write("	daq_flash_seconds {0.1}\n")
                        elif "daq_adjust_flash" in lines[line]:
                            fo.write("	daq_adjust_flash {0}\n")
                        else:
                            fo.write(lines[line])
                    fo.write('\n')




def main():

    print "CEM"
    cem = AnalyzeFile('cem')
    cem.WriteOutput()
    print "End CEM"

    print "AEM"
    aem = AnalyzeFile('aem')
    aem.WriteOutput()
    print "End AEM"

    print "CEO"
    ceo = AnalyzeFile('ceo')
    ceo.WriteOutput()
    print "End CEO"

    print "AEO"
    aeo = AnalyzeFile('aeo')
    aeo.WriteOutput()
    print "End AEO"

    print "EE"
    ee = AnalyzeFile('ee')
    ee.WriteOutput()
    print "End EE"

    print "EI"
    ei = AnalyzeFile('ei')
    ei.WriteOutput()
    print "End EI"

    print "EIL4"
    eil4 = AnalyzeFile('eil4')
    eil4.WriteOutput()
    print "End EIL4"

    print "POLC"
    polc = AnalyzeFile('polc')
    polc.WriteOutput()
    print "End POLC"

    print "POLA"
    pola = AnalyzeFile('pola')
    pola.WriteOutput()
    print "End POLA"

    print "POLEI"
    polei = AnalyzeFile('polei')
    polei.WriteOutput()
    print "End POLEI"

if __name__ == "__main__":
    main()


