#include "calc.h"

/* Document-class: Calc::C
 *
 * Calc complex number.
 *
 * A complex number consists of a real and an imaginary part, both of which
 * are Calc::Q objects.
 *
 * Wraps the libcalc C type `COMPLEX*`.
 */
VALUE cC;

void
cc_free(void *p)
{
    cfree((COMPLEX *) p);
}

const rb_data_type_t calc_c_type = {
    "Calc::C",
    {0, cc_free, 0},
    0, 0
#ifdef RUBY_TYPED_FREE_IMMEDIATELY
        , RUBY_TYPED_FREE_IMMEDIATELY
#endif
};

VALUE
cc_alloc(VALUE klass)
{
    return TypedData_Wrap_Struct(klass, &calc_c_type, 0);
}

/* Creates a new complex number.
 */
static VALUE
cc_initialize(int argc, VALUE * argv, VALUE self)
{
    COMPLEX *cself;
    NUMBER *qre, *qim;
    VALUE re, im;
    setup_math_error();

    if (rb_scan_args(argc, argv, "11", &re, &im) == 1) {
        qre = value_to_number(re, 1);
        cself = qqtoc(qre, &_qzero_);
        qfree(qre);
    }
    else {
        qre = value_to_number(re, 1);
        qim = value_to_number(im, 1);
        cself = qqtoc(qre, qim);
        qfree(qre);
        qfree(qim);
    }
    DATA_PTR(self) = cself;

    return self;
}

static VALUE
cc_initialize_copy(VALUE obj, VALUE orig)
{
    COMPLEX *corig;

    if (obj == orig) {
        return obj;
    }
    if (!ISCVALUE(orig)) {
        rb_raise(rb_eTypeError, "wrong argument type");
    }
    corig = DATA_PTR(orig);
    DATA_PTR(obj) = clink(corig);
    return obj;
}

/* class definition */

void
define_calc_c(VALUE m)
{
    cC = rb_define_class_under(m, "C", rb_cData);
    rb_define_alloc_func(cC, cc_alloc);
    rb_define_method(cC, "initialize", cc_initialize, -1);
    rb_define_method(cC, "initialize_copy", cc_initialize_copy, 1);
}
