#define disjoint           struct
#define variantof(S)       (S)._variant
#define emptyvariant(D, V) (D){ V }
#define variant(D, V, ...) (D){ V, __VA_ARGS__ }
#define variants(...)      enum { __VA_ARGS__ } _variant; union
#define match(S)           switch (variantof(S))
