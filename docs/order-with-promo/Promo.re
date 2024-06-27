[@react.component]
let make = (~items as _: list(Item.t), ~date as _: Js.Date.t) => <div />;

[@warning "-27"]
module AddOnApply = {
  // #region add-on-apply
  [@react.component]
  let make =
      (~items: list(Item.t), ~date: Js.Date.t, ~onApply: float => unit) =>
    // #endregion add-on-apply
    <div />;
};

[@warning "-27"]
module DefaultValue = {
  // #region default-value
  [@react.component]
  let make =
      (
        ~items: list(Item.t),
        ~date: Js.Date.t,
        ~onApply: float => unit=_ => (),
      ) =>
    // #endregion default-value
    <div />;
};

let _ =
  (discount, onApply) => {
    // #region use-effect
    React.useEffect1(
      () => {
        switch (discount) {
        | `NoSubmittedCode
        | `CodeError(_)
        | `DiscountError(_) => ()
        | `Discount(value) => onApply(value)
        };
        None;
      },
      [|discount|],
    );
    // #endregion use-effect
    ();
  };

let _ =
  (discount, onApply) => {
    // #region use-effect-helper
    RR.useEffect1(
      () => {
        switch (discount) {
        | `NoSubmittedCode
        | `CodeError(_)
        | `DiscountError(_) => ()
        | `Discount(value) => onApply(value)
        };
        None;
      },
      discount,
    );
    // #endregion use-effect-helper
    ();
  };
