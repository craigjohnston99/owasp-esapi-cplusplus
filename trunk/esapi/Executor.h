#ifndef _Executor_h_
#define _Executor_h_

#include <fstream>
#include <list>
#include <string>

namespace esapi
{
/**
 * The Executor interface is used to run an OS command with reduced security risk.
 *
 * <p>Implementations should do as much as possible to minimize the risk of
 * injection into either the command or parameters. In addition, implementations
 * should timeout after a specified time period in order to help prevent denial
 * of service attacks.</p>
 *
 * <p>The class should perform logging and error handling as
 * well. Finally, implementation should handle errors and generate an
 * ExecutorException with all the necessary information.</p>
 *
 * <p>The reference implementation does all of the above.</p>
 *
 * @since June 11, 2011
 */
	class Executor
	{
	public:
		virtual ExecuteResult executeSystemCommand(std::fstream, std::list) =0 throw ExecutorException;
		virtual ExecuteResult executeSystemCommand(std::fstream, std::list, std::fstream, Codec, bool, bool) =0 throw ExecutorException;

		virtual ~Executor() {};
	};
};

#endif	// _Executor_h_