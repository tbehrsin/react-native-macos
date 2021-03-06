/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <AppKit/AppKit.h>

#import <React/RCTComponent.h>

@class RCTShadowView;

@interface NSView (React) <RCTComponent>

/**
 * RCTComponent interface.
 */
- (NSArray<NSView *> *)reactSubviews NS_REQUIRES_SUPER;
- (NSView *)reactSuperview NS_REQUIRES_SUPER;
- (void)insertReactSubview:(NSView *)subview atIndex:(NSInteger)atIndex NS_REQUIRES_SUPER;
- (void)removeReactSubview:(NSView *)subview NS_REQUIRES_SUPER;

/**
 * Layout direction of the view.
 * Internally backed to `semanticContentAttribute` property.
 * Defaults to `LeftToRight` in case of ambiguity.
 */
@property (nonatomic, assign) NSUserInterfaceLayoutDirection reactLayoutDirection;

/**
 * z-index, used to override sibling order in didUpdateReactSubviews.
 */
@property (nonatomic, assign) NSInteger reactZIndex;

/**
 * The reactSubviews array, sorted by zIndex. This value is cached and
 * automatically recalculated if views are added or removed.
 */
@property (nonatomic, copy, readonly) NSArray<NSView *> *sortedReactSubviews;

/**
 * Updates the subviews array based on the reactSubviews. Default behavior is
 * to insert the sortedReactSubviews into the UIView.
 */
- (void)didUpdateReactSubviews;

/**
 * Used by the UIIManager to set the view frame.
 * May be overriden to disable animation, etc.
 */
- (void)reactSetFrame:(CGRect)frame;

/**
 * Used to improve performance when compositing views with translucent content.
 */
- (void)reactSetInheritedBackgroundColor:(NSColor *)inheritedBackgroundColor;

/**
 * This method finds and returns the containing view controller for the view.
 */
- (NSViewController *)reactViewController;

/**
 * This method attaches the specified controller as a child of the
 * the owning view controller of this view. Returns NO if no view
 * controller is found (which may happen if the view is not currently
 * attached to the view hierarchy).
 */
- (void)reactAddControllerToClosestParent:(NSViewController *)controller;

/**
 * Focus manipulation.
 */
- (void)reactFocus;
- (void)reactFocusIfNeeded;
- (void)reactBlur;

/**
 * UIView replacement
 */
@property (nonatomic, assign) BOOL clipsToBounds;

#if RCT_DEV

/**
 Tools for debugging
 */

@property (nonatomic, strong, setter=_DEBUG_setReactShadowView:) RCTShadowView *_DEBUG_reactShadowView;

#endif

@end
