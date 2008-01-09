/*---------------------------------------------------------------------\
|								       |
|		       __   __	  ____ _____ ____		       |
|		       \ \ / /_ _/ ___|_   _|___ \		       |
|			\ V / _` \___ \ | |   __) |		       |
|			 | | (_| |___) || |  / __/		       |
|			 |_|\__,_|____/ |_| |_____|		       |
|								       |
|				core system			       |
|							 (C) SuSE GmbH |
\----------------------------------------------------------------------/

  File:		YIntField.h

  Author:	Stefan Hundhammer <sh@suse.de>

/-*/

#ifndef YIntField_h
#define YIntField_h

#include "YWidget.h"

class YIntFieldPrivate;

using std::string;


/**
 * IntField: Input field for integer values. Enforces input range between a
 * specified minimum and maximum value.
 **/
class YIntField : public YWidget
{
protected:
    /**
     * Constructor.
     *
     * Create an IntField with 'label' as the caption, and the specified minimum
     * and maximum values.
     *
     * Note that YWidgetFactory::createIntField() also has an 'initialValue'
     * parameter that is not used here (because the current value is not stored
     * in this base class, but in the derived class).
     **/
    YIntField( YWidget *	parent,
	       const string & 	label,
	       int		minValue,
	       int		maxValue );

public:
    /**
     * Destructor.
     **/
    virtual ~YIntField();

    /**
     * Return a descriptive name of this widget class for logging,
     * debugging etc.
     **/
    virtual const char * widgetClass() const { return "YIntField"; }

    /**
     * Get the current value (the number entered by the user or set from the
     * outside) of this IntField.
     *
     * Derived classes are required to implement this.
     **/
    virtual int value() = 0;

    /**
     * Set the current value (the number entered by the user or set from the
     * outside) of this IntField. This method enforces 'val to be between
     * minValue and maxValue.
     **/
    void setValue( int val ) { setValueInternal( enforceRange( val ) ); }

protected:

    /**
     * Set the current value (the number entered by the user or set from the
     * outside) of this IntField. 'val' is guaranteed to be between minValue
     * and maxValue; no further checks are required.
     *
     * Derived classes are required to implement this method.
     **/
    virtual void setValueInternal( int val ) = 0;

    /**
     * Enforce 'val' to be between minValue and maxValue.
     * Return a value that is in range. This does not change the internally
     * stored value of this IntField in any way.
     **/
    int enforceRange( int val ) const;

public:

    /**
     * Return the minimum value.
     **/
    int minValue() const;

    /**
     * Set a new minimum value. If the current value is less than that, it will
     * be set to the new minimum.
     **/
    void setMinValue( int val );

    /**
     * Return the maximum value.
     **/
    int maxValue() const;

    /**
     * Set a new maximum value. If the current value is greater than that, it
     * will be set to the new maximum.
     **/
    void setMaxValue( int val );

    /**
     * Get the label (the caption above the input field).
     **/
    string label() const;

    /**
     * Set the label (the caption above the input field).
     *
     * Derived classes are free to reimplement this, but they should call this
     * base class method at the end of the overloaded function.
     **/
    virtual void setLabel( const string & label );

    /**
     * Set a property.
     * Reimplemented from YWidget.
     *
     * This function may throw YUIPropertyExceptions.
     *
     * This function returns 'true' if the value was successfully set and
     * 'false' if that value requires special handling (not in error cases:
     * those are covered by exceptions).
     **/
    virtual bool setProperty( const string & propertyName,
			      const YPropertyValue & val );

    /**
     * Get a property.
     * Reimplemented from YWidget.
     *
     * This method may throw YUIPropertyExceptions.
     **/
    virtual YPropertyValue getProperty( const string & propertyName );

    /**
     * Return this class's property set.
     * This also initializes the property upon the first call.
     *
     * Reimplemented from YWidget.
     **/
    virtual const YPropertySet & propertySet();

    /**
     * Get the string of this widget that holds the keyboard shortcut.
     *
     * Reimplemented from YWidget.
     **/
    virtual string shortcutString() { return label(); }

    /**
     * Set the string of this widget that holds the keyboard shortcut.
     *
     * Reimplemented from YWidget.
     **/
    virtual void setShortcutString( const string & str )
	{ setLabel( str ); }

    /**
     * The name of the widget property that will return user input.
     * Inherited from YWidget.
     **/
    const char * userInputProperty() { return YUIProperty_Value; }


private:

    /**
     * Save the widget's user input to a macro recorder.
     * Intentionally declared as "private" so all macro recording internals are
     * handled by the abstract libyui level, not by a specific UI.
     **/
    virtual void saveUserInput( YMacroRecorder *macroRecorder );


    ImplPtr<YIntFieldPrivate>	priv;
};


#endif // YIntField_h