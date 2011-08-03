#ifndef _AccessReferenceMap_h_
#define _AccessReferenceMap_h_

#include <set>

namespace esapi
{
/**
 * The AccessReferenceMap interface is used to map from a set of internal
 * direct object references to a set of indirect references that are safe to
 * disclose publicly. This can be used to help protect database keys,
 * filenames, and other types of direct object references. As a rule, developers
 * should not expose their direct object references as it enables attackers to
 * attempt to manipulate them.
 * <P>
 * Indirect references are handled as strings, to facilitate their use in HTML.
 * Implementations can generate simple integers or more complicated random
 * character strings as indirect references. Implementations should probably add
 * a constructor that takes a list of direct references.
 * <P>
 * Note that in addition to defeating all forms of parameter tampering attacks,
 * there is a side benefit of the AccessReferenceMap. Using random strings as indirect object
 * references, as opposed to simple integers makes it impossible for an attacker to
 * guess valid identifiers. So if per-user AccessReferenceMaps are used, then request
 * forgery (CSRF) attacks will also be prevented.
 *
 * <pre>
 * Set fileSet = new HashSet();
 * fileSet.addAll(...); // add direct references (e.g. File objects)
 * AccessReferenceMap map = new AccessReferenceMap( fileSet );
 * // store the map somewhere safe - like the session!
 * String indRef = map.getIndirectReference( file1 );
 * String href = &quot;http://www.aspectsecurity.com/esapi?file=&quot; + indRef );
 * ...
 * // if the indirect reference doesn't exist, it's likely an attack
 * // getDirectReference throws an AccessControlException
 * // you should handle as appropriate
 * String indref = request.getParameter( &quot;file&quot; );
 * File file = (File)map.getDirectReference( indref );
 * </pre>
 *
 * <P>
 *
 * @author Jeff Williams (jeff.williams@aspectsecurity.com)
 * @author Chris Schmidt (chrisisbeef@gmail.com)
 * @author David Anderson (david.anderson@aspectsecurity.com)
 */
	class AccessReferenceMap
	{
	public:
		virtual Iterator iterator() =0;
		virtual <T> K getIndirectReference(T directReference) =0;
		virtual <T> T getDirectReference(K indirectReference) =0 throw  AccessControlException;
		virtual <T> K addDirectReference(T direct) =0;
		virtual <T> K removeDirectReference(T direct) =0 throw AccessControlException;
		virtual void update(std:set directReferences) =0;

		virtual ~AccessReferenceMap() {};
	};
};

#endif	// _AccessReferenceMap_h_