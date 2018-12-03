#!/bin/bash

function GetURL ()
{
   local URL=$1
   local DATE=$2
   local INDEX=$3
   
   echo "* Downloading entry: ${INDEX}"
   wget -q -O entries/${INDEX} "${URL}"
   
   echo "   Extracting contents."
   local storing_lines=0
   local first_line=1
   
   cat "entries/${INDEX}" | while read line
   do
      # I'm already looking for content lines?
      if [ "${storing_lines}" == "1" ]; then
         # Check if the line is an end for me.
         if [[ "${line}" == *posts-nav-link* ]]; then
            storing_lines=0
         # I'm storing lines. Check if the line is useful. For that, it should
         # be a paragraf.
         elif [ "${line:0:3}" == "<p>" ]; then
            # Is this the first line of the HTML?
            if [ "${first_line}" == "1" ]; then
               # It is a little bit longer. Make special process.
               local size=${#line}
               local length=$((size-4))
               local clean_line=dummy
               
               for i in {1..1000}
               do
                  if [ "${line:${i}:4}" == "</a>" ]; then
                     size=$((i+4))
                     clean_line=${line:${size}}
                  fi
               done
               
               for i in {1..1000}
               do
                  if [ "${clean_line:${i}:4}" == "</p>" ]; then
                     clean_line=${clean_line:0:${i}}
                  fi
               done
               
               echo "${clean_line}" >> contents/${INDEX}
               first_line=0
            else
               # It is an easy line. Remove the first 3 chars and last 4
               # It is something like "<p>LOL</p>"
               local size=${#line}
               local length=$((size-7))
               local clean_line=${line:3:${length}}
               echo "${clean_line}" >> contents/${INDEX}
            fi
         fi
      # No, check if the line contains the key I'm checking for
      elif [[ "${line}" == *articleBody* ]]; then
         # Enable flag
         storing_lines=1
      fi
   done
   
   echo "   Scanning contents."
   first_line=1
   local zone=dummy
   local municipality=dummy
   local municipality_found=0
   local state=dummy
   local state_found=0   
   local keys_found=NONE
   
   if [[ -f municipality.tmp ]]; then
      rm municipality.tmp
   fi
   
   if [[ -f state.tmp ]]; then
      rm state.tmp
   fi
   
   if [[ -f zone.tmp ]]; then
      rm zone.tmp
   fi
   
   if [[ -f keys.tmp ]]; then
      rm keys.tmp
   fi
   
   # Read the file, line by line
   cat "contents/${INDEX}" | while read line
   do
      # Create local variable for the line. The line corresponds to the
      # notice info, but it could contain the state and municipality.
      local remaining_line=dummy
      
      # If this is the first line, it must contain the state and the
      # municipality.
      if [ "${first_line}" == "1" ]; then
         # Disable the flag.
         first_line=0
         
         echo "Validating line: ${line}"
         
         # Try to scan for the municipality value
         for i in {1..50}
         do
            if [ "${municipality_found}" == "0" ]; then
               if [ "${line:${i}:1}" == "," ]; then
                  municipality=${line:0:${i}}
                  municipality_found=1
                  local index=$((i+2))
                  remaining_line=${line:${index}}
                  echo "   Municipality: ${municipality}"
                  echo -n ${municipality} > municipality.tmp
               fi
            fi
         done
         
         # Now, it must come the state
         for i in {1..50}
         do
            if [ "${state_found}" == "0" ]; then
               if [ "${remaining_line:${i}:2}" == ".-" ]; then
                  state=${remaining_line:0:${i}}
                  state_found=1
                  local index=$((i+3))
                  remaining_line=${remaining_line:${index}}
                  echo "   State:        ${state}"
                  echo -n ${state} > state.tmp
               fi
            fi
         done
      else
         remaining_line=${line}
      fi
            
      # Don't scan if there isn't a state
      if [ "${state}" != "dummy" ]; then
         lowercase_string=${remaining_line,,}
         
         # See if this line contains the missing zone
         if [[ "${zone}" == "dummy" ]]; then
            for file in zones/*
            do
               cat "${file}" | while read zone_line
               do
                  # Store it as lowercase
                  current_zone=${zone_line,,}
                  
                  if [[ "${remaining_line}" == "*${current_zone}*" ]]; then
                     zone=${zone_line}
                     echo "   Zone:         ${zone}"
                     echo -n ${zone} > zone.tmp
                  fi
               done
            done
         fi
         
         if [[ "${lowercase_string}" == *asesinada* ]]; then
            if [[ "${keys_found}" != *ASESINATO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=ASESINATO
               else
                  keys_found="${keys_found}:ASESINATO"
               fi
               
               echo -n ":ASESINATO" >> keys.tmp
            fi
         fi
                  
         if [[ "${lowercase_string}" == *asesinado* ]]; then
            if [[ "${keys_found}" != *ASESINATO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=ASESINATO
               else
                  keys_found="${keys_found}:ASESINATO"
               fi
               
               echo -n ":ASESINATO" >> keys.tmp
            fi
         fi
         
         if [[ "${lowercase_string}" == *homicid* ]]; then
            if [[ "${keys_found}" != *ASESINATO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=ASESINATO
               else
                  keys_found="${keys_found}:ASESINATO"
               fi
               
               echo -n ":ASESINATO" >> keys.tmp
            fi
         fi
         
         if [[ "${lowercase_string}" == *mata* ]]; then
            if [[ "${keys_found}" != *ASESINATO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=ASESINATO
               else
                  keys_found="${keys_found}:ASESINATO"
               fi
               
               echo -n ":ASESINATO" >> keys.tmp
            fi
         fi
         
         if [[ "${lowercase_string}" == *mato* ]]; then
            if [[ "${keys_found}" != *ASESINATO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=ASESINATO
               else
                  keys_found="${keys_found}:ASESINATO"
               fi
               
               echo -n ":ASESINATO" >> keys.tmp
            fi
         fi
         
         if [[ "${lowercase_string}" == *disparar* ]]; then
            if [[ "${keys_found}" != *DISPAROS* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=DISPAROS
               else
                  keys_found="${keys_found}:DISPAROS"
               fi
               
               echo -n ":DISPAROS" >> keys.tmp
            fi
         fi
         
         if [[ "${lowercase_string}" == *disparo* ]]; then
            if [[ "${keys_found}" != *DISPAROS* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=DISPAROS
               else
                  keys_found="${keys_found}:DISPAROS"
               fi
               
               echo -n ":DISPAROS" >> keys.tmp
            fi
         fi
         
         if [[ "${lowercase_string}" == *secuestrar* ]]; then
            if [[ "${keys_found}" != *SECUESTRO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=SECUESTRO
               else
                  keys_found="${keys_found}:SECUESTRO"
               fi
               
               echo -n ":SECUESTRO" >> keys.tmp
            fi
         fi
         
         if [[ "${lowercase_string}" == *secuestro* ]]; then
            if [[ "${keys_found}" != *SECUESTRO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=SECUESTRO
               else
                  keys_found="${keys_found}:SECUESTRO"
               fi
               
               echo -n ":SECUESTRO" >> keys.tmp
            fi
         fi
         
         if [[ "${lowercase_string}" == *secuestrad* ]]; then
            if [[ "${keys_found}" != *SECUESTRO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=SECUESTRO
               else
                  keys_found="${keys_found}:SECUESTRO"
               fi
               
               echo -n ":SECUESTRO" >> keys.tmp
            fi
         fi
         
         if [[ "${lowercase_string}" == *robo* ]]; then
            if [[ "${keys_found}" != *ASALTO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=ASALTO
               else
                  keys_found="${keys_found}:ASALTO"
               fi
               
               echo -n ":ASALTO" >> keys.tmp
            fi
         fi
         
         if [[ "${lowercase_string}" == *roba* ]]; then
            if [[ "${keys_found}" != *ASALTO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=ASALTO
               else
                  keys_found="${keys_found}:ASALTO"
               fi
               
               echo -n ":ASALTO" >> keys.tmp
            fi
         fi
      fi
   done
   
   if [[ -f state.tmp ]]; then
      cat state.tmp >> db.csv
   else
      echo -n "NONE" >> db.csv
   fi
   
   echo -n "," >> db.csv
   
   if [[ -f municipality.tmp ]]; then
      cat municipality.tmp >> db.csv
   else
      echo -n "NONE" >> db.csv
   fi
   
   echo -n "," >> db.csv
   
   if [[ -f zone.tmp ]]; then
      cat zone.tmp >> db.csv
   else
      echo -n "NONE" >> db.csv
   fi
   
   echo -n ",${DATE},${INDEX}," >> db.csv
   
   if [[ -f keys.tmp ]]; then
      cat keys.tmp >> db.csv
   else
      echo -n "NONE" >> db.csv
   fi
   
   echo ",${URL}" >> db.csv
}

function CleanFolders ()
{
   echo "* Clear contents"
   echo "*"
   if [ -d "xmls/" ]; then
      rm -R xmls/
   fi
   mkdir xmls

   if [ -f "urls.txt" ]; then
      rm urls.txt
   fi
   
   if [ -f "db.csv" ]; then
      rm db.csv
   fi

   if [ -d "entries/" ]; then
      rm -R entries/
   fi
   mkdir entries

   if [ -d "contents/" ]; then
      rm -R contents/
   fi
   mkdir contents
}

# ********** #
# REAL START #
# ********** #

XML_URL=http://www.lapoliciaca.com/post_part
URL_KEY=loc
DATE_KEY=lastmod

CleanFolders

echo "* Downloading XML files."
# Download enough contents as to fill
for i in {1..2}
do
   output_file=""
   
   if [ ${i} -lt 10 ]; then
      output_file=xmls/p000${i}.xml
   elif [ ${i} -lt 100 ]; then
      output_file=xmls/p00${i}.xml
   elif [ ${i} -lt 1000 ]; then
      output_file=xmls/p0${i}.xml
   else
      output_file=xmls/p${i}.xml
   fi
   
   echo "* Downloading: ${output_file} <- ${XML_URL}${i}.xml"
   wget -q -O ${output_file} ${XML_URL}${i}.xml
done

echo "*"
echo "* Extracting files..."
for file in xmls/*
do
   echo "* Extracting file: ${file}"
   
   cat "${file}" | while read line
   do
      tmp=${line%<*}
      
      if [[ "${tmp}" == *${URL_KEY}* ]]; then
         echo "${tmp:5}" >> urls.txt
      elif [[ "${tmp}" == *${DATE_KEY}* ]]; then
         echo "${tmp:9}" >> urls.txt
      fi
   done
done

echo "*"
echo "* Getting pages contents..."
LINE_URL=dummy
LINE_DATE=dummy
BUFFERED=0
i=0
cat "urls.txt" | while read line
do
   if [ "${BUFFERED}" == "0" ]; then
      LINE_URL=${line}
      BUFFERED=1
   else
      LINE_DATE=${line}
      BUFFERED=0
      INDEX=dummy
      
      i=$((i+1))
      
      if [ $i -lt 10 ]; then
         INDEX=000${i}
      elif [ $i -lt 100 ]; then
         INDEX=00${i}
      elif [ $i -lt 1000 ]; then
         INDEX=0${i}
      else
         INDEX=${i}
      fi
      
      GetURL "${LINE_URL}" "${LINE_DATE}" ${INDEX}
   fi
done
