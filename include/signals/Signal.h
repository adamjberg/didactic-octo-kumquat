#pragma once

#include <functional>
#include <vector>

template<class... Args>
class Signal {
	typedef std::function<void( Args... )> Callback;
public:
	std::vector<Callback> callbacks;

	Signal( Callback callback = Callback() ){};
	int add( const Callback &callback ) {
		callbacks.push_back( callback );
		return callbacks.size();
	};
	void remove( int index ) {
		callbacks.erase( callbacks.begin() + index );
	};
	void dispatch( Args... args ) {
		for( Callback callback : this->callbacks )
		{
			callback( args... );
		}
	};
};

