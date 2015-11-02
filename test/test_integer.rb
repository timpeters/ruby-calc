require 'minitest_helper'

class TestInteger < Minitest::Test
  def test_class_exists
    refute_nil Calc::Z
  end

  def test_initialization
    assert_instance_of Calc::Z, Calc::Z.new(42)                 # Fixnum
    assert_instance_of Calc::Z, Calc::Z.new(0x4000000000000000) # Bignum
    assert_instance_of Calc::Z, Calc::Z.new(Calc::Z.new(42))    # Calc::Z
  end

  def test_dup
    z1 = Calc::Z.new(42)
    z2 = z1.dup
    assert_equal "42", z2.to_s
    refute_equal z1.object_id, z2.object_id
  end

  def test_equal
    assert_equal Calc::Z.new(3), Calc::Z.new(3)
    assert_equal Calc::Z.new(4), 4
    assert_equal 5, Calc::Z.new(5)
    refute_equal Calc::Z.new(6), Calc::Z.new(7)
    refute_equal Calc::Z.new(8), 9
    refute_equal 10, Calc::Z.new(11)
    refute_equal Calc::Z.new(12), "dog"
  end

  def test_comparisons
    assert_equal  0, Calc::Z.new(3) <=> Calc::Z.new(3)
    assert_equal -1, Calc::Z.new(4) <=> Calc::Z.new(5)
    assert_equal  1, Calc::Z.new(7) <=> Calc::Z.new(6)
    assert_equal  0, Calc::Z.new(8) <=> 8
    assert_equal -1, Calc::Z.new(9) <=> 10
    assert_equal  1, Calc::Z.new(12) <=> 11

    # <=> is supposed to return nil if objects aren't comparable
    assert_nil Calc::Z.new(3) <=> "cat"
    assert_nil "cat" <=> Calc::Z.new(4)
  end
  
  def test_to_s
    assert_equal "42",                  Calc::Z.new(42).to_s
    assert_equal "4611686018427387904", Calc::Z.new(0x4000000000000000).to_s
    assert_equal "42",                  Calc::Z.new(Calc::Z.new(42)).to_s
  end
end
