#ifndef ASSERT_H
#define ASSERT_H

#define ENABLE_ASSERTIONS 1
#define ENABLE_WARNINGS 1

void ReportError( const char *errorType,
                  const char *file,
				  int line,
				  const char *formatMessage = 0,
				  ... );

#define TriggerBreakpoint() do { __debugbreak(); } while( 0, 0 )

#ifndef VoidExpression
#define VoidExpression( expr ) \
	do{ \
		( void )sizeof( expr ); \
	}while( 0, 0 )
#endif

#if ENABLE_ASSERTIONS

	#define Assert( expr, ... ) \
		do { \
			if( !( expr ) ) { \
				ReportError( "Assert", \
                             __FILE__, \
							 __LINE__, \
							 ##__VA_ARGS__ ); \
				TriggerBreakpoint(); \
			} \
		} while( 0,0 )

    #define AssertAlways( ... ) \
		do { \
			ReportError( "Assert", \
                            __FILE__, \
							__LINE__, \
							##__VA_ARGS__ ); \
			TriggerBreakpoint(); \
		} while( 0,0 )

#else // if !ENABLE_ASSERTIONS
	#define Assert( expr ) do{ VoidExpression( expr ); } while( 0, 0 )
    #define AssertAlways( expr ) do{ VoidExpression( expr ); } while( 0, 0 )
#endif // ENABLE_ASSERTIONS

#if ENABLE_WARNINGS

	#define Warning( expr, ... ) \
		do { \
			if( !( expr ) ) { \
				ReportError( "Warning", \
                             __FILE__, \
							 __LINE__, \
							 ##__VA_ARGS__ ); \
				TriggerBreakpoint(); \
			} \
		} while( 0, 0 )

    #define WarningAlways( ... ) \
		do { \
			ReportError( "Warning", \
                         __FILE__, \
					     __LINE__, \
						 ##__VA_ARGS__ ); \
			TriggerBreakpoint(); \
		} while( 0, 0 )

#else // if !ENABLE_WARNINGS
    #define Warning( expr ) do{ VoidExpression( expr ); } while( 0, 0 )
    #define WarningAlways( expr ) do{ VoidExpression( expr ); } while( 0, 0 )
#endif // ENABLE_WARNINGS

#endif // ASSERT_H