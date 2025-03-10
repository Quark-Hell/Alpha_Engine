#define ACLASS()

#define SERIALIZE_DATA(...)		\
friend bitsery::Access;		\
template <typename BIT>		\
void serialize(BIT& ser) {		\
ser(__VA_ARGS__);		\
}


#define SERIALIZE_DERIVEDDATA(...)		\
friend bitsery::Access;		\
template <typename BIT>		\
void serialize(BIT& ser) {		\
ser.ext(*this, bitsery::ext::BaseClass<Data>{});		\
ser(__VA_ARGS__);		\
}

