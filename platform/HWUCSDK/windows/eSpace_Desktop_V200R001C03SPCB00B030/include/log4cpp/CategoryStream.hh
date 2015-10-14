/*
 * CategoryStream.hh
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_CATEGORYSTREAM_HH
#define _LOG4CPP_CATEGORYSTREAM_HH

#include <log4cpp/Portability.hh>
#include <log4cpp/Priority.hh>
#include <ios>
#ifdef LOG4CPP_HAVE_SSTREAM
#include <sstream>
#endif
#include <log4cpp/Manipulator.hh>
#include <memory>




namespace log4cpp {

    class LOG4CPP_EXPORT Category;
    class LOG4CPP_EXPORT CategoryStream;    
    /**
     * eol manipulator
     **/
    LOG4CPP_EXPORT CategoryStream& eol (CategoryStream& os);

    /**
     * left manipulator
     **/
    LOG4CPP_EXPORT CategoryStream& left (CategoryStream& os);

    /**
     * This class enables streaming simple types and objects to a category.
     * Use category.errorStream(), etc. to obtain a CategoryStream class.
     **/
    class LOG4CPP_EXPORT CategoryStream {
        public:

        /**
         * Construct a CategoryStream for given Category with given priority.
         * @param category The category this stream will send log messages to.
         * @param priority The priority the log messages will get or 
         * Priority::NOTSET to silently discard any streamed in messages.
         **/
        CategoryStream(Category& category, Priority::Value priority);

        /**
         * Destructor for CategoryStream
         **/
        ~CategoryStream();
        
        /**
         * Returns the destination Category for this stream.
         * @returns The Category.
         **/
        inline Category& getCategory() const { return _category; };

        /**
         * Returns the priority for this stream.
         * @returns The priority.
         **/
        inline Priority::Value getPriority() const throw() { 
            return _priority; 
        };

        /**
         * Flush the contents of the stream buffer to the Category and
         * empties the buffer.
         **/
        void flush();

        /**
         * Stream in arbitrary types and objects.  
         * @param t The value or object to stream in.
         * @returns A reference to itself.
         **/
		template<typename T> CategoryStream& operator<<(const T& t) {
            if (getPriority() != Priority::NOTSET) {
                if (!_buffer) {
                    _buffer = new std::ostringstream;
					if (!(_buffer)) {
                        // XXX help help help
                    }
                }
                (*_buffer) << t;
            }
            return *this;
        }
	
	template<typename T> 
 	CategoryStream& operator<<(const std::string& t) {
            if (getPriority() != Priority::NOTSET) {
                if (!_buffer) {
                    _buffer = new std::ostringstream;
					if (!(_buffer)) {
                        // XXX help help help
                    }
                }
                (*_buffer) << t;
            }
            return *this;
        }
#if LOG4CPP_HAS_WCHAR_T != 0
        template<> 
        CategoryStream& operator<<(const std::wstring& t) {
            if (getPriority() != Priority::NOTSET) {
                if (!_wbuffer) {
                    _wbuffer = new std::wostringstream;
                    if (!(_wbuffer)) {
                        // XXX help help help
                    }
                }
                (*_wbuffer) << t;
            }
            return *this;
        }
#endif
        /**
         * Set the width output on CategoryStream
         **/
		std::streamsize width(std::streamsize wide );


        private:
        Category& _category;
        Priority::Value _priority;
	union {
	    std::ostringstream* _buffer;
#if LOG4CPP_HAS_WCHAR_T != 0
            std::wostringstream* _wbuffer;
#endif
	};

	public:
	typedef CategoryStream& (*cspf) (CategoryStream&);

	CategoryStream& operator<< (cspf);
        LOG4CPP_EXPORT friend CategoryStream& eol (CategoryStream& os);
        LOG4CPP_EXPORT friend CategoryStream& left (CategoryStream& os);
   };


//#ifdef LOG4CPP_HAS_WCHAR_T
//   //char* ×¨³É wchar*
//   inline std::wostringstream& operator << (std::wostringstream& oss, const char* p)
//   {
//       std::auto_ptr<wchar_t> wcharPtr = log4cpp::to_wstr(p);
//
//       oss << wcharPtr.get();
//       
//       return oss;
//   }
//
//   inline std::wostringstream& operator << (std::wostringstream& oss, const std::string& p)
//   {
//       std::auto_ptr<wchar_t> wcharPtr = to_wstr(p.c_str());
//
//       oss << wcharPtr.get();
//       
//       return oss;
//   }
//#else
//
//   inline std::ostringstream& operator << (std::ostringstream& oss, const wchar_t* p)
//   {
//       std::auto_ptr<char> charPtr = to_str(p);
//
//       oss << charPtr.get();
//       
//       return oss;
//   }
//
//   inline std::ostringstream& operator << (std::ostringstream& oss, const std::wstring& p)
//   {
//       std::auto_ptr<char> charPtr = to_str(p.c_str());
//
//       oss << charPtr.get();
//       
//       return oss;
//   }
//#endif

}
#endif // _LOG4CPP_CATEGORYSTREAM_HH
